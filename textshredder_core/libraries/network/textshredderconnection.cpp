#include "textshredderconnection.h"
#include "../synchronization/filemanager.h"
#include "models/filerequestpacket.h"

TextShredderConnection::TextShredderConnection(QObject *parent) :
	QObject(parent)
{
	connectionListener = QSharedPointer<ConnectionListener> (new ConnectionListener(this));
	connectionListener.data()->listen();
	quint16 port = connectionListener.data()->serverPort();
	qDebug() << "port " << port;
}

void TextShredderConnection::deleteServer(ConnectionListener *obj)
{
	obj->deleteLater();
}
void TextShredderConnection::socketDescriptorReady(int socketDescriptor)
{
	socket.setSocketDescriptor(socketDescriptor);
	disconnect(connectionListener.data(), SIGNAL(newConnection(int)),
			   this, SLOT(socketDescriptorReady(int)));
	connectionListener.data()->close();
	connectionListener.clear();

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
	QTextStream inputStream(&socket);
	QString buffer;

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
	qDebug("TextShredderConnection::emitNewIncomingPacket(TextShredderPacket &packet)");
	if (packet.isEditPacket ()) {
		qDebug("EditPacketContent");
		emit incomingEditPacketContent(packet.getContent());
	} else if (packet.isFileDataPacket ()) {
		qDebug("FileDatapacket");
		emit incomingFileDataPacketContent(packet.getContent());
	} else if (packet.isFileRequestPacket()) {
		qDebug("RequestPacket");
		handleFileRequestPacket(packet);
	} else if (packet.isSetAliasPacket()) {
		qDebug("SetAliasPacket");
		emit incomingSetAliasPacketContent(packet.getContent());
	} else if (packet.isSyncableFilesPacket()) {
		qDebug("SyncableFilesPacket");
		emit incomingSyncableFilesPacket(packet.getContent());
	}
}

void TextShredderConnection::handleFileRequestPacket(TextShredderPacket &packet)
{
	quint16 port = FileRequestPacket::getPort(packet);
	QString requestedFileName = FileRequestPacket::getFileAlias(packet);

	try {
		QString name(socket.peerAddress().toString());
		QSharedPointer<SyncableFile> file = FileManager::Instance()->getSyncableFileWithName(requestedFileName);
		file.data()->createSynchronizationWithPortAndAddress(port, name);
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
	qDebug("We have an error...");
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

	return connectionListener.data()->serverPort();
}

void TextShredderConnection::sendPacket(TextShredderPacket & packet)
{
	write(packet);
}

