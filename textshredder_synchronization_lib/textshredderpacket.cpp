#include "textshredderpacket.h"

TextShredderPacket::TextShredderPacket(QObject *parent,
                                       TextShredderHeader * header,
                                       QByteArray * content) :
    QObject(parent), header(header), content(content)
{
}

bool TextShredderPacket::isEditPacket()
{
    return false;
}
