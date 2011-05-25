#include "textshredderconnection.h"
#include "../synchronization/filemanager.h"
#include "models/filerequestpacket.h"

TextShredderConnection::~TextShredderConnection()
{
	qDebug() << "Destructing TSConnection";
}

TextShredderConnection::TextShredderConnection(QObject *parent,
											   QString &hostName,
											   int port ,
											   bool startImmediately) :
	QObject(parent)
{
	socket = QSharedPointer<QTcpSocket>(new QTcpSocket());
	setupSignalsForSocket();
	this->port = port;
	hostAddressString = hostName;

	this->status = Disconnected;

	if (startImmediately) {
		socket.data()->connectToHost (hostName, port);
	}
}

void TextShredderConnection::startConnection()
{
	socket.data()->connectToHost(hostAddressString, port);
}

TextShredderConnection::TextShredderConnection(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	socket = QSharedPointer<QTcpSocket>(new QTcpSocket());
	setupSignalsForSocket();
	socket.data()->setSocketDescriptor(socketDescriptor);
	this->status = Neutral;
}

void TextShredderConnection::setupSignalsForSocket()
{
	connect(FileManager::Instance(), SIGNAL(sendFileRequest(TextShredderPacket&)),
			this, SLOT(sendPacket(TextShredderPacket &)));

	connect(socket.data(), SIGNAL(readyRead()), this, SLOT(read()));

	connect(socket.data(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	connect(socket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	connect(socket.data(), SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));
}

void TextShredderConnection::breakDownSignalsForSocket()
{
	qDebug() << "TextShredderConnection::breakDownSignalsForSocket()";
	disconnect(FileManager::Instance(), SIGNAL(sendFileRequest(TextShredderPacket&)),
			this, SLOT(sendPacket(TextShredderPacket &)));

	disconnect(socket.data(), SIGNAL(readyRead()), this, SLOT(read()));

	disconnect(socket.data(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	disconnect(socket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	disconnect(socket.data(), SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));
}

void TextShredderConnection::read()
{
	QTextStream inputStream(socket.data());
	QString buffer;

	inputStream.setAutoDetectUnicode(false);
	inputStream.setCodec("UTF-8" );
	while(!inputStream.atEnd()) {
		 buffer.append(inputStream.readAll());
	}

	QByteArray packetData;
	packetData.append(buffer);
	parser.handleData(packetData);

	while(parser.hasMorePackets()) {
		TextShredderPacket * packet = parser.nextPacket();
		emitNewIncomingPacket(*packet);
		packet->deleteLater();
		inputStream.reset();
	}
}

void TextShredderConnection::emitNewIncomingPacket(TextShredderPacket &packet)
{
	if (packet.isEditPacket ()) {
		emit incomingEditPacketContent(packet.getContent(), packet.getHeader().getConnectionHandle());
	} else if (packet.isFileDataPacket()) {
		quint16 destination =  packet.getHeader().getConnectionHandle();
		emit incomingFileDataPacket(packet,destination);
	} else if (packet.isFileRequestPacket()) {
		emit incomingFileRequestPacket(packet);
	} else if (packet.isSetAliasPacket()) {
		emit incomingSetAliasPacketContent(packet.getContent());
	} else if (packet.isSyncableFilesPacket()) {
		emit incomingSyncableFilesPacket(packet.getContent());
	} else if (packet.isEndSynchronizationPacket()) {
		emit incomingEndSynchronizationPacket(packet.getHeader().getConnectionHandle());
	} else if (packet.isOnlineUsersPacket()) {
		emit incomingOnlineUsersPacket(packet);
	}
}

void TextShredderConnection::write(TextShredderPacket &packet)
{
	if (socket.isNull()) {
		qDebug("Socket is null");
		return;
	}

	QTextStream outputStream(socket.data());


	outputStream.setAutoDetectUnicode(false);
	outputStream.setCodec("UTF-8");

	QByteArray raw;
	packet.getHeader().appendToQByteArray(raw);
	raw.append(packet.getContent());
	outputStream << raw;
	outputStream.flush();
}

void TextShredderConnection::socketStateChanged(QAbstractSocket::SocketState state)
{
	if (state == QAbstractSocket::ConnectedState) {
		this->status = Connected;
		emit statusChanged(this->status, QAbstractSocket::UnknownSocketError);
	}
}

void TextShredderConnection::socketError(QAbstractSocket::SocketError error)
{
	this->status = Error;
	emit statusChanged(this->status, error);
}

void TextShredderConnection::clientHasDisconnected()
{
	qDebug() << "TextShredderConnection::clientHasDisconnected()";
	status = Disconnected;
	breakDownSignalsForSocket();

	emit clientDisconnected();
}

QString TextShredderConnection::getPeerAdress() {
	QHostAddress peerAdress = socket.data()->peerAddress();
	return peerAdress.toString();
}

unsigned int TextShredderConnection::getPort()
{
	return port;
}

void TextShredderConnection::sendPacket(TextShredderPacket & packet)
{
	write(packet);
}

