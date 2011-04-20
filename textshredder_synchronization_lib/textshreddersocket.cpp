#include "textshreddersocket.h"

TextShredderSocket::TextShredderSocket(QObject *parent, int socketDescriptor) :
    QTcpSocket(parent)
{
	this->setSocketDescriptor(socketDescriptor);
}

TextShredderPacket * TextShredderSocket::readPacket()
{
	qDebug("aa");
	QByteArray buffer;
	do{
		buffer.append(this->readAll());
	} while (buffer.size() == 0);

	qDebug() << QString::number(buffer.size());
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
