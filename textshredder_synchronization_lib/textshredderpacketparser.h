#ifndef TEXTSHREDDERPACKETPARSER_H
#define TEXTSHREDDERPACKETPARSER_H

#include <QByteArray>
#include "textshredderpacket.h"
#include "textshredderheader.h"

namespace TextShredderPacketParser
{
    /*
     * Convert a QByteArray to a TextShredderPacket.
     *
     * @param QByteArray raw packet
     * @Return TextShredderPacket
     */
    TextShredderPacket* makePacketFromBytes(QByteArray * bytes);
}

#endif // TEXTSHREDDERPACKETPARSER_H
