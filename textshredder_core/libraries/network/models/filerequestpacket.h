#ifndef FILEREQUESTPACKET_H
#define FILEREQUESTPACKET_H

#include "textshredderpacket.h"

class FileRequestPacket : public TextShredderPacket
{
public:
	FileRequestPacket(QObject *parent, qint16 port, QString &fileAlias);
	static quint16 getPort(TextShredderPacket &);
	static QString getFileAlias(TextShredderPacket &);
};

#endif // FILEREQUESTPACKET_H
