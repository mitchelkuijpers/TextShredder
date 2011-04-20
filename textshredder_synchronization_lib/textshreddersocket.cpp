#include "textshreddersocket.h"

TextShredderSocket::TextShredderSocket(QObject *parent, int socketDescriptor) :
    QTcpSocket(parent)
{
	this->setSocketDescriptor(socketDescriptor);
}

TextShredderPacket * TextShredderSocket::readPacket()
{
	qDebug("TextShredderSocket::readPacket()");
	qDebug("-- waiting for ready read");
	//this->waitForReadyRead ();
	qDebug("-- ready read");
	QByteArray buffer;//(this->readAll());
	while (this->bytesAvailable() == 0) {
		this->waitForReadyRead(100);
	}
	buffer.append(this->readAll());;
	qDebug("-- did read");

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
