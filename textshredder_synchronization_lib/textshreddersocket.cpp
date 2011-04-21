#include "textshreddersocket.h"

TextShredderSocket::TextShredderSocket(QObject *parent, int socketDescriptor) :
	QTcpSocket(parent)
{
	mutex.lock();
	this->connect(this, SIGNAL(readyRead()), this, SLOT(socketIsReadyForReading()));
	this->setSocketDescriptor(socketDescriptor);

}

TextShredderPacket * TextShredderSocket::readPacket()
{
	qDebug("TextShredderSocket::readPacket()------------------START");
	qDebug("Wait for socketIsReadyForReading slot");
	qDebug() << this;
	mutex.lock();
	qDebug("got it start reading");
	QByteArray buffer;
	buffer.append(this->readAll());
	this->flush();
	qDebug("done with the readall");

	qDebug() << QString::number(buffer.size());
	qDebug("TextShredderSocket::readPacket()----------------END");
	return TextShredderPacketParser::makeAllocatedPacketFromBytes(&buffer);
}

void TextShredderSocket::writePacket(TextShredderPacket * packet)
{
	QByteArray buffer;
	QByteArray content(packet->getContent());
	packet->getHeader().appendToQByteArray(buffer);
	buffer.append(content);
	this->write(buffer);
	qDebug("Wait till writing is done");
}

void TextShredderSocket::socketIsReadyForReading()
{
	qDebug("socketIsReadyForReading unlock mutex");
	qDebug() << this;
	mutex.unlock();
}

void TextShredderSocket::socketIsDoneWithWriting(qint64 bytes)
{
	qDebug("socketIsDoneWithWriting");
	qDebug() << this;
	qDebug() << bytes;
}

void TextShredderSocket::socketError(QAbstractSocket::SocketError theError)
{
	qDebug("There was an error");
	qDebug() << theError;
}
