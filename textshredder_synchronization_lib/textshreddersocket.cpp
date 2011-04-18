#include "textshreddersocket.h"

TextShredderSocket::TextShredderSocket(QObject *parent, int socketDescriptor) :
    QTcpSocket(parent)
{
	this->setSocketDescriptor(socketDescriptor);
}

TextShredderPacket * TextShredderSocket::readPacket()
{
	QByteArray buffer(this->read(this->bytesAvailable()));
	return TextShredderPacketParser::makePacketFromBytes(&buffer);
}

void TextShredderSocket::writePacket(TextShredderPacket * packet)
{
	QByteArray buffer;
	QByteArray content(packet->getContent());
	packet->getHeader()->appendToQByteArray(buffer);
	buffer.append(content);
	this->write(buffer);
}
