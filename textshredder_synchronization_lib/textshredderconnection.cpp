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
	socket.setSocketDescriptor(socketDescriptor);
	this->status = Neutral;
}

void TextShredderConnection::read()
{
	qDebug("Before read");
	QTextStream inputStream(&socket);

	QString buffer;
	while(!inputStream.atEnd()) {
		 buffer = inputStream.readAll();
		 qDebug() << buffer;
	}

	QByteArray packet;
	packet.append(buffer);
	TextShredderPacket * tsPacket = TextShredderPacketParser::makeAllocatedPacketFromBytes(&packet);
	emit newIncomingPacket(*tsPacket);
	delete tsPacket;
	qDebug("After read");
}

void TextShredderConnection::write(TextShredderPacket &packet)
{
	qDebug("Before write");
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
	if(	state == QAbstractSocket::UnconnectedState) {
		status = Disconnected;
		emit statusChanged(this->status);
	} else if (state == QAbstractSocket::ConnectedState) {
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

QString TextShredderConnection::getPeerAdress() {
	QHostAddress peerAdress = socket.peerAddress();
	return peerAdress.toString();
}
