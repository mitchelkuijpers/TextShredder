#include "textshredderconnection.h"

TextShredderConnection::TextShredderConnection(QObject *parent,
											   QString &hostName,
											   int port) :
	QObject(parent)
{
	socket.connectToHost (hostName, port);
	setupSignalsForSocket();

	this->status = Disconnected;
}

TextShredderConnection::TextShredderConnection(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	qDebug("set SocketDescriptor!");

	setupSignalsForSocket();
	socket.setSocketDescriptor(socketDescriptor);
	this->status = Neutral;
}

void TextShredderConnection::setupSignalsForSocket()
{
	connect(&socket, SIGNAL(readyRead()), this, SLOT(read()));

	connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	connect(&socket, SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));
}

void TextShredderConnection::read()
{
	qDebug("Before read");
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
	}
	qDebug("After read");
}

void TextShredderConnection::emitNewIncomingPacket(TextShredderPacket &packet)
{
	if (packet.isEditPacket ()) {
		emit incomingEditPacketContent(packet.getContent());
	} else if (packet.isFileDataPacket ()) {
		emit incomingFileDataPacketContent(packet.getContent());
	} else if (packet.isFileRequestPacket()) {
		emit incomingFileRequestPacketContent(packet.getContent());
	} else if (packet.isSetAliasPacket()) {
		emit incomingSetAliasPacketContent(packet.getContent());
	}
}

void TextShredderConnection::write(TextShredderPacket &packet)
{
	qDebug("before write");
	QTextStream outputStream(&socket);
	QByteArray raw;
	packet.getHeader().appendToQByteArray(raw);
	raw.append(packet.getContent());

	outputStream << raw;
	outputStream.flush();
	qDebug("After write");
}

void TextShredderConnection::socketStateChanged(QAbstractSocket::SocketState state)
{
	qDebug() << QString("TSConnection State changed: ") << state;
	if (state == QAbstractSocket::ConnectedState) {
		this->status = Neutral;
		emit statusChanged(this->status);
	}
	qDebug("After State changed");
}

void TextShredderConnection::socketError(QAbstractSocket::SocketError error)
{
	qDebug("Before Socket error");
	// @TODO make good error messages
	qDebug() << error;
	this->status = Error;
	emit statusChanged(this->status);
	qDebug("After Socket error");
}

void TextShredderConnection::clientHasDisconnected()
{
	qDebug() << QString("Client disconnected");
	status = Disconnected;
	emit clientDisconnected();
}

QString TextShredderConnection::getPeerAdress() {
	QHostAddress peerAdress = socket.peerAddress();
	return peerAdress.toString();
}
