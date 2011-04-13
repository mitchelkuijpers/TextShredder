#ifndef TEXTSHREDDERSOCKET_H
#define TEXTSHREDDERSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "textshredderpacketparser.h"

class TextShredderSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TextShredderSocket(QObject *parent);

signals:

public slots:

private:
    TextShredderPacketParser * textShredderPacketParser;

};

#endif // TEXTSHREDDERSOCKET_H
