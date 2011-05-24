#include "setaliaspacket.h"

SetAliasPacket::SetAliasPacket(QObject *parent, QString alias) :
		TextShredderPacket(parent, kPacketTypeSetAlias)
{
	QByteArray bytes;
	bytes.append(alias);
	this->setContent(bytes);
}
