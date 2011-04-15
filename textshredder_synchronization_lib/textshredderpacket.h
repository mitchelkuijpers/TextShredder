#ifndef TEXTSHREDDERPACKET_H
#define TEXTSHREDDERPACKET_H

#include <QObject>
#include "textshredderheader.h"

class TextShredderPacket : public QObject
{
    Q_OBJECT
public:
    TextShredderPacket(QObject *parent, TextShredderHeader *, QByteArray *);
    bool isEditPacket();

signals:

public slots:

private:
    TextShredderHeader * textShredderHeader;
    QByteArray * content;
};

#endif // TEXTSHREDDERPACKET_H
