#include "textshredderconnection.h"

TextShredderConnection::TextShredderConnection(QObject *parent,
											   QString &hostName,
											   int port) :
	QObject(parent)
{
	socket.connectToHost (hostName, port);

	connect(&socket, SIGNAL(readyRead()), this, SLOT(read()));

	connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	connect(&socket, SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));

	this->status = Disconnected;
}

TextShredderConnection::TextShredderConnection(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	qDebug("set SocketDescriptor!");

	connect(&socket, SIGNAL(readyRead()), this, SLOT(read()));

	connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
			SLOT(socketStateChanged(QAbstractSocket::SocketState)));

	connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
			SLOT(socketError(QAbstractSocket::SocketError)));

	connect(&socket, SIGNAL(disconnected()), this,
			SLOT(clientHasDisconnected()));

	socket.setSocketDescriptor(socketDescriptor);
	this->status = Neutral;
}

void TextShredderConnection::read()
{
	QTextStream inputStream(&socket);
	QString buffer;

	while(!inputStream.atEnd()) {
		 buffer.append(inputStream.readAll());
	}
	qDebug() << buffer;

	QByteArray packetData;
	packetData.append(buffer);
	parser.handleData(packetData);
	qDebug() << QString("parsed Data: ") << packetData.length();
	while(parser.hasMorePackets()) {
		qDebug("handlepacket");
		TextShredderPacket * packet = parser.nextPacket();
		emit newIncomingPacket(*packet);
		delete packet;
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
