#ifndef TEXTSHREDDERPACKETPARSER_H
#define TEXTSHREDDERPACKETPARSER_H

#include <QByteArray>
#include "models/textshredderpacket.h"
#include "models/textshredderheader.h"

class TextShredderPacketParser
{
public:
	TextShredderPacketParser();
	/**
	 * Convert a QByteArray to a TextShredderPacket. Returns is NULL if something
	 * went wrong
	 *
	 * @param a raw packet
	 * @return The packet it created from a QByteArray.
	 * @throws QString when the protocolVersion is wrong
	 *
	 */
	TextShredderPacket* makeAllocatedPacketFromBytes(QByteArray * bytes);
	void handleData(QByteArray &);
	bool hasMorePackets();
	TextShredderPacket * nextPacket();
private:
	void queueIncompletPacket();
	QList<TextShredderPacket *> queuedPackets;
	TextShredderPacket * incompletePacket;
	QByteArray incompleteData;

};

#endif // TEXTSHREDDERPACKETPARSER_H
