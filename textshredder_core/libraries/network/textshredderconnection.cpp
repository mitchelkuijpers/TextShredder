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
											   int port) :
	QObject(parent), socket(this)
{
	socket.connectToHost (hostName, port);
	setupSignalsForSocket();
	this->port = port;
	this->status = Disconnected;
}

TextShredderConnection::TextShredderConnection(QObject *parent,
											   QHostAddress &address,
											   int port) :
	QObject(parent), socket(this)
{
	qDebug("e");
	socket.connectToHost(address, port);
	qDebug("f");
	setupSignalsForSocket();
	qDebug("g");
	this->port = port;
	qDebug("h");
	this->status = Neutral;
	qDebug("i");
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
		delete packet;
		inputStream.reset();
	}
}

void TextShredderConnection::emitNewIncomingPacket(TextShredderPacket &packet)
{
	if (packet.isEditPacket ()) {
		emit incomingEditPacketContent(packet.getContent());
	} else if (packet.isFileDataPacket ()) {
		emit incomingFileDataPacketContent(packet.getContent());
	} else if (packet.isFileRequestPacket()) {
		handleFileRequestPacket(packet);
	} else if (packet.isSetAliasPacket()) {
		emit incomingSetAliasPacketContent(packet.getContent());
	}
}

void TextShredderConnection::handleFileRequestPacket(TextShredderPacket &packet)
{
	quint16 port = FileRequestPacket::getPort(packet);
	QString requestedFileName = FileRequestPacket::getFileAlias(packet);

	try {
		QString name("name");
		SyncableFile *file = &FileManager::Instance()->getSyncableFileWithName(requestedFileName);
		file->createSynchronizationWithPortAndAddress(port, name);
	} catch (QString exception) {
		//Some error occured. Problably no such file.
	}
}

void TextShredderConnection::write(TextShredderPacket &packet)
{
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
		this->status = Neutral;
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

