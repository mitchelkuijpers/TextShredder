#ifndef TEXTSHREDDERSOCKET_H
#define TEXTSHREDDERSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <textshredderpacketparser.h>

class TextShredderSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TextShredderSocket(QObject *parent = 0);



signals:

public slots:

private:
    TextshredderPacketParser *textShredderPacketParser;

};

#endif // TEXTSHREDDERSOCKET_H
