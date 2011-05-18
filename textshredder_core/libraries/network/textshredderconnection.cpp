#include "textshredderconnection.h"
#include "../synchronization/filemanager.h"
#include "models/filerequestpacket.h"

TextShredderConnection::TextShredderConnection(QObject *parent) :
	QObject(parent)
{
	socket.open(QIODevice::ReadWrite);
}
TextShredderConnection::TextShredderConnection(QObject *parent,
											   QString &hostName,
											   int port ,
											   bool startImmediately) :
	QObject(parent)
{
	setupSignalsForSocket();
	this->port = port;
	hostAddressString = hostName;

	this->status = Disconnected;

	if (startImmediately) {
		socket.connectToHost (hostName, port);
	}
}

void TextShredderConnection::startConnection()
{
	socket.connectToHost(hostAddressString, port);
}

TextShredderConnection::TextShredderConnection(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	setupSignalsForSocket();
	socket.setSocketDescriptor(socketDescriptor);
	this->status = Neutral;
}

void TextShredderConnection::setupSignalsForSocket()
{
	connect(FileManager::Instance(), SIGNAL(sendFileRequest(TextShredderPacket&)),
			this, SLOT(sendPacket(TextShredderPacket &)));

	connect(&socket, SIGNAL(readyRead()), this, SLOT(read()));

	connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	connect(&socket, SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));
}

void TextShredderConnection::breakDownSignalsForSocket()
{
	disconnect(FileManager::Instance(), SIGNAL(sendFileRequest(TextShredderPacket&)),
			this, SLOT(sendPacket(TextShredderPacket &)));

	disconnect(&socket, SIGNAL(readyRead()), this, SLOT(read()));

	disconnect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	disconnect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	disconnect(&socket, SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));
}

void TextShredderConnection::read()
{
	qDebug("TextShredderConnection::read()");
	QTextStream inputStream(&socket);
	QString buffer;

	qDebug("2");
	while(!inputStream.atEnd()) {
		 buffer.append(inputStream.readAll());
	}

	qDebug("3");
	QByteArray packetData;
	packetData.append(buffer);
	parser.handleData(packetData);

	qDebug("4");
	while(parser.hasMorePackets()) {
		TextShredderPacket * packet = parser.nextPacket();
		emitNewIncomingPacket(*packet);
		packet->deleteLater();
		inputStream.reset();
	}
}

void TextShredderConnection::emitNewIncomingPacket(TextShredderPacket &packet)
{
	qDebug("TextShredderConnection::emitNewIncomingPacket(TextShredderPacket &packet)");
	if (packet.isEditPacket ()) {
		emit incomingEditPacketContent(packet.getContent());
	} else if (packet.isFileDataPacket ()) {
		emit incomingFileDataPacketContent(packet.getContent());
	} else if (packet.isFileRequestPacket()) {
		handleFileRequestPacket(packet);
	} else if (packet.isSetAliasPacket()) {
		emit incomingSetAliasPacketContent(packet.getContent());
	} else if (packet.isSyncableFilesPacket()) {
		qDebug("TextShredderConnection::emitNewIncomingPacket syncablefilespacket");
		emit incomingSyncableFilesPacket(packet.getContent());
	}
}

void TextShredderConnection::handleFileRequestPacket(TextShredderPacket &packet)
{
	quint16 port = FileRequestPacket::getPort(packet);
	QString requestedFileName = FileRequestPacket::getFileAlias(packet);

	try {
		QString name("name");
		SyncableFile *file = FileManager::Instance()->getSyncableFileWithName(requestedFileName);
		file->createSynchronizationWithPortAndAddress(port, name);
	} catch (QString exception) {
		//Some error occured. Problably no such file.
	}
}

void TextShredderConnection::write(TextShredderPacket &packet)
{
	qDebug("Will write");
	qDebug() << QString::number(packet.getHeader().getPacketType());
	QTextStream outputStream(&socket);
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
		emit statusChanged(this->status);
	}
}

void TextShredderConnection::socketError(QAbstractSocket::SocketError error)
{
	// @TODO make good error messages
	qDebug() << error;
	this->status = Error;
	emit statusChanged(this->status);
}

void TextShredderConnection::clientHasDisconnected()
{
	status = Disconnected;
	breakDownSignalsForSocket();
	emit clientDisconnected();
}

QString TextShredderConnection::getPeerAdress() {
	QHostAddress peerAdress = socket.peerAddress();
	return peerAdress.toString();
}

unsigned int TextShredderConnection::getPort()
{
	return port;
}

quint16 TextShredderConnection::getLocalPort()
{
	return socket.localPort();
}

void TextShredderConnection::sendPacket(TextShredderPacket & packet)
{
	write(packet);
}

