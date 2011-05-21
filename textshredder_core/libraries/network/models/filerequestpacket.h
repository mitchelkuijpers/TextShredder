#ifndef FILEREQUESTPACKET_H
#define FILEREQUESTPACKET_H

#include "textshredderpacket.h"
#include <stdlib.h>

class FileRequestPacket : public TextShredderPacket
{
public:
	FileRequestPacket(QObject *parent, quint16 port, QString &fileAlias);
	static quint16 getSourceHandle(TextShredderPacket &);
	static QString getFileIdentifier(TextShredderPacket &);
};

#endif // FILEREQUESTPACKET_H
