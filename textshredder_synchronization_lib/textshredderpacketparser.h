#ifndef TEXTSHREDDERPACKETPARSER_H
#define TEXTSHREDDERPACKETPARSER_H

#include <QByteArray>
#include "textshredderpacket.h"
#include "textshredderheader.h"

namespace TextShredderPacketParser
{
	/**
	 * Convert a QByteArray to a TextShredderPacket. Returns is NULL if something
	 * went wrong
	 *
	 * @param a raw packet
	 * @return The packet it created from a QByteArray.
	 * @throws QString when the protocolVersion is wrong
	 *
	 */
    TextShredderPacket* makePacketFromBytes(QByteArray * bytes);
}

#endif // TEXTSHREDDERPACKETPARSER_H
