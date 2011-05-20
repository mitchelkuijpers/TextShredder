#include "filedatapacket.h"


FileDataPacket::FileDataPacket(QObject *parent, QByteArray &content, quint16 connectionHandle) :
		TextShredderPacket(parent)
{

}

QByteArray & FileDataPacket::getFileDataContent(TextShredderPacket &packet)
{

}

quint16 FileDataPacket::getConnectionHandle(TextShredderPacket &packet)
{

}
