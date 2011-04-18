#include "textshredderpacketparser.h"

namespace TextShredderPacketParser
{
    TextShredderPacket * makePacketFromBytes(QByteArray * bytes)
    {
        QByteArray protocolVersion = bytes->mid(kProtocolVersionOffset,(int) sizeof(unsigned char));
        if((int)protocolVersion.toInt() != kProtocolVersion) {
            throw QString("protocolError");
        }
        QByteArray length = bytes->mid(kPacketLengthOffset,
                                      (int) sizeof(unsigned int));
        QByteArray type = bytes->mid(kPacketTypeOffset,
                                    (int) sizeof(unsigned char));
        bool temp;
        bool * ok = &temp;
        QByteArray content = QByteArray();
        length.toInt(ok);
        if(*ok == 1) {
              content.append(bytes->mid(kHeaderLength, (int) length.toInt()));
        } else {
            throw QString("Length could not be converted to an int");
        }
        TextShredderHeader * header = new TextShredderHeader(
                    NULL,
                    (unsigned char) *protocolVersion.data(),
                    (unsigned int) length.toInt(),
                    (unsigned char)*type.data());
        return new TextShredderPacket(
                    NULL, header, &content);
    }
}
