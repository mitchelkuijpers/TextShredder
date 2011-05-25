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

	/**
	 * Check the incoming data on completeness, after the checks append it to the incoming data array.
	 * @param QByteArray& the incoming data
	 */
	void handleData(QByteArray &);
	/**
	 * Check if there are any packets queued.
	 * @return True or false according to if there are any packets queued.
	 */
	bool hasMorePackets();
	/**
	 * Get the first element from the queuedPackets and return it.
	 * @return The textshredderpacket
	 */
	TextShredderPacket * nextPacket();
private:
	/**
	 * Queue the incomplete packet to be sended again.
	 */
	void queueIncompletPacket();
	QList<TextShredderPacket *> queuedPackets;
	TextShredderPacket * incompletePacket;
	QByteArray incompleteData;

};

#endif // TEXTSHREDDERPACKETPARSER_H
