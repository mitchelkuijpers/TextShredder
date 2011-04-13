#ifndef TEXTSHREDDERPACKETPARSER_H
#define TEXTSHREDDERPACKETPARSER_H

#include <QObject>
#include "textshredderpacket.h"

class TextShredderPacketParser : public QObject
{
    Q_OBJECT
public:
    TextShredderPacketParser(QObject *parent);

signals:

public slots:

private:
    TextShredderPacket *textShredderPacket;

};

#endif // TEXTSHREDDERPACKETPARSER_H
