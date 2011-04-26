#include "textshredderconnection.h"

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
	this->status = TextShredderConnection::Neutral;
}

void TextShredderConnection::read()
{
	QTextStream inputStream(&socket);

	QString buffer;
	while(!inputStream.atEnd()) {
		 buffer = inputStream.readAll();
		 qDebug() << buffer;
	}

	QByteArray packet;
	packet.append(buffer);
	TextShredderPacket * tsPacket = TextShredderPacketParser::makeAllocatedPacketFromBytes(&packet);
	emit newIncomingPacket( *tsPacket);
}

void TextShredderConnection::write(TextShredderPacket packet)
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
	if(	state == QAbstractSocket::UnconnectedState) {
		status = TextShredderConnection::Disconnected;
		emit statusChanged(this->status);
	} else if (state == QAbstractSocket::ConnectedState) {
		this->status = TextShredderConnection::Neutral;
		emit statusChanged(this->status);
	}
}

void TextShredderConnection::socketError(QAbstractSocket::SocketError error)
{
	// @TODO make good error messages
	this->status = TextShredderConnection::Error;
	emit statusChanged(this->status);
}

QString TextShredderConnection::getPeerAdress() {
	QHostAddress peerAdress = socket.peerAddress();
	return peerAdress.toString();
}
