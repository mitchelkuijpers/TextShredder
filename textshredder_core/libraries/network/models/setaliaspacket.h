#ifndef SETALIASPACKET_H
#define SETALIASPACKET_H

#include "textshredderpacket.h"

class SetAliasPacket : public TextShredderPacket
{
	Q_OBJECT
public:
	/**
	 * Constructor, appends the useraliasses to a bytearray
	 * @param *parent To have access to the Q methods
	 * @param alias The alias string
	 */
	SetAliasPacket(QObject *parent, QString alias);
};

#endif // SETALIASPACKET_H
