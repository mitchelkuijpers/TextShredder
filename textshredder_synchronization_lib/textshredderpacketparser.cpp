#include "textshredderpacketparser.h"

namespace TextShredderPacketParser
{
	TextShredderPacket * makeAllocatedPacketFromBytes(QByteArray * bytes)
    {
		QByteArray protocolVersion = bytes->mid(kProtocolVersionOffset,
												(int) sizeof(unsigned char));
		if(protocolVersion.data()[0] != kProtocolVersion) {
			throw QString(protocolVersion); //wrong protocolVersion
        }

        QByteArray length = bytes->mid(kPacketLengthOffset,
                                      (int) sizeof(unsigned int));
        QByteArray type = bytes->mid(kPacketTypeOffset,
                                    (int) sizeof(unsigned char));
		unsigned int iLength = *((unsigned int *)length.data());

		QByteArray content(bytes->mid(kHeaderLength -1 , iLength + 1));
		TextShredderHeader header(
                    NULL,
					(unsigned char) * protocolVersion.data(),
					(unsigned int) iLength,
					(unsigned char) * type.data());
        return new TextShredderPacket(
					NULL, header, content);
    }
}
