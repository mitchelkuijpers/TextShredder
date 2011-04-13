#ifndef TEXTSHREDDERPACKETPARSER_H
#define TEXTSHREDDERPACKETPARSER_H

#include <QObject>
#include <textshredderpacket.h>

class TextshredderPacketParser : public QObject
{
    Q_OBJECT
public:
    TextshredderPacketParser(QObject *parent = 0);

signals:

public slots:

private:
    TextShredderPacket *textShredderPacket;

};

#endif // TEXTSHREDDERPACKETPARSER_H
