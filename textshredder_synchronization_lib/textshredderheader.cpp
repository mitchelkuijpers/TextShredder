#include "textshredderheader.h"

TextShredderHeader::TextShredderHeader( QObject *parent ) :
                                        QObject(parent),
                                        protocolVersion(kProtocolVersion),
                                        contentLength(0),
                                        packetType(0)
{

}

TextShredderHeader::TextShredderHeader( QObject *parent,
                                        unsigned char protocolVersion,
                                        unsigned int contentLength,
                                        unsigned char packetType ) :
QObject(parent),

		protocolVersion(protocolVersion), contentLength(contentLength),
                packetType(packetType)
{
}

TextShredderHeader::TextShredderHeader( QObject *parent ,
                                        const QByteArray &buffer ) :
QObject(parent)
{
    int offset = 0;
    protocolVersion = buffer[offset];

    offset += sizeof(protocolVersion);
    memcpy(&contentLength, (const void *) &(buffer.data()[1]), sizeof(unsigned int));

    offset += sizeof(contentLength);
    packetType = buffer[offset];
}

void TextShredderHeader::appendToQByteArray( QByteArray &buffer )
{
    buffer.append( protocolVersion );
    buffer.append( (const char *)&contentLength, (int) sizeof(unsigned int) );
    buffer.append( packetType );
}

unsigned char TextShredderHeader::getProtocolVersion()
{
    return protocolVersion;
}

unsigned char TextShredderHeader::getPacketType()
{
    return packetType;
}

unsigned int TextShredderHeader::getContentLength()
{
    return contentLength;
}

void TextShredderHeader::setProtocolVersion( unsigned char newValue )
{
    protocolVersion = newValue;
}

void TextShredderHeader::setContentLength( unsigned int newValue )
{
    contentLength = newValue;
}

void TextShredderHeader::setPacketType( unsigned char newValue )
{
    packetType = newValue;
}
