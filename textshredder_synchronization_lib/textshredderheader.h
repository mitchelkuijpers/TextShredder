#ifndef TEXTSHREDDERHEADER_H
#define TEXTSHREDDERHEADER_H

#include <QtCore/QtCore>

#define kProtocolVersion 1

#define kPacketTypeEdits 0
#define kPacketTypeFileData 1
#define kPacketTypeFileRequest 2

#define kHeaderLength 6

class TextShredderHeader : QObject
{
public:
    TextShredderHeader();
    TextShredderHeader(unsigned char protocolVersion, unsigned int contentLength, unsigned char packetType);
    TextShredderHeader( const QByteArray & );
    void appendToQByteArray( QByteArray & );

    unsigned char getProtocolVersion();
    unsigned int getPacketType();
    unsigned int getContentLength();

private:
    unsigned char protocolVersion;
    unsigned int contentLength;
    unsigned char packetType;
};

#endif // TEXTSHREDDERHEADER_H
