#ifndef ENDSYNCHRONIZATIONPACKET_H
#define ENDSYNCHRONIZATIONPACKET_H

#include "textshredderpacket.h"

class EndSynchronizationPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	/**
	 * Constructor, sets the packettype and destination
	 * @param *parent To use the Q methods
	 * @param destination the destination to send the packet to
	 */
	EndSynchronizationPacket(QObject *parent, unsigned int destination);
};

#endif // ENDSYNCHRONIZATIONPACKET_H
