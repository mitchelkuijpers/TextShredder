#include "textshreddersocket.h"

TextShredderSocket::TextShredderSocket(QObject *parent) :
    QTcpSocket(parent)
{
}

TextShredderPacket * TextShredderSocket::readPacket()
{
    return NULL;
}

void TextShredderSocket::writePacket(TextShredderPacket *)
{

}
