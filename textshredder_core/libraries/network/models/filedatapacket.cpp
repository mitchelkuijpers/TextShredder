#include "filedatapacket.h"


FileDataPacket::FileDataPacket(QObject *parent, QByteArray &content, quint16 connectionHandle) :
		TextShredderPacket(parent, kPacketTypeFileData)
{
	QByteArray newContent;
	unsigned short value = connectionHandle;
	char *pointer = (char *)&value;
	newContent.append(pointer, 2);
	newContent.append(content);
	this->setContent(newContent);
}

QByteArray FileDataPacket::getFileDataContent(TextShredderPacket &packet)
{
	return packet.getContent().mid(2);
}

quint16 FileDataPacket::getConnectionHandle(TextShredderPacket &packet)
{
	QByteArray handlePart = packet.getContent().left(2);
	quint16 returnValue;
	memcpy(&returnValue, handlePart.data(), 2);
	return returnValue;
}
