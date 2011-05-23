#ifndef ENDSYNCHRONIZATIONPACKET_H
#define ENDSYNCHRONIZATIONPACKET_H

#include "textshredderpacket.h"

class EndSynchronizationPacket : public TextShredderPacket
{
	Q_OBJECT

public:
	EndSynchronizationPacket(QObject *parent, unsigned int destination);
};

#endif // ENDSYNCHRONIZATIONPACKET_H
