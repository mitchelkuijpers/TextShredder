#include "endsynchronizationpacket.h"

EndSynchronizationPacket::EndSynchronizationPacket(QObject *parent, unsigned int destination)
	: TextShredderPacket(parent, kPacketTypeSynchronizationEnd, destination)
{
}
