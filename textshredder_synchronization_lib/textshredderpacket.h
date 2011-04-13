#ifndef TEXTSHREDDERPACKET_H
#define TEXTSHREDDERPACKET_H

#include <QObject>
#include <textshredderheader.h>

class TextShredderPacket : public QObject
{
    Q_OBJECT
public:
    TextShredderPacket(QObject *parent = 0);


signals:

public slots:

private:
    TextShredderHeader *textShredderHeader;
    QByteArray *Content;

};

#endif // TEXTSHREDDERPACKET_H
