#include "availablefilesrequestpacket.h"

AvailableFilesRequestPacket::AvailableFilesRequestPacket()
{
	TextShredderPacket::TextShredderPacket(this, kPacketTypeAvailableFilesRequest);
}
