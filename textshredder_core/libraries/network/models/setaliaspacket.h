#ifndef SETALIASPACKET_H
#define SETALIASPACKET_H

#include "textshredderpacket.h"

class SetAliasPacket : public TextShredderPacket
{
	Q_OBJECT
public:
	SetAliasPacket(QObject *parent, QString alias);
};

#endif // SETALIASPACKET_H
