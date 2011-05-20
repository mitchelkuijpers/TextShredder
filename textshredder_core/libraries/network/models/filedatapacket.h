#ifndef FILEDATAPACKET_H
#define FILEDATAPACKET_H

#include "textshredderpacket.h"

class FileDataPacket : public TextShredderPacket
{
	Q_OBJECT
public:
	FileDataPacket(QObject *parent, QByteArray &content, quint16 connectionHandle);
	static QByteArray & getFileDataContent(TextShredderPacket &packet);
	static quint16 getConnectionHandle(TextShredderPacket &packet);
};

#endif // FILEDATAPACKET_H
