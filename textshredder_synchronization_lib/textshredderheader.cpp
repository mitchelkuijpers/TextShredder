#include "textshredderheader.h"

TextShredderHeader::TextShredderHeader() :
        protocolVersion(kProtocolVersion), contentLength(0), packetType(0)
{

}

TextShredderHeader::TextShredderHeader( unsigned char protocolVersion,
                                        unsigned int contentLength,
                                        unsigned char packetType ) :

		protocolVersion(protocolVersion), contentLength(contentLength),
		packetType(packetType)
{
}

TextShredderHeader::TextShredderHeader( const QByteArray &buffer )
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

unsigned int TextShredderHeader::getPacketType()
{
    return packetType;
}

unsigned int TextShredderHeader::getContentLength()
{
    return contentLength;
}

unsigned char setProtocolVersion()
{

}

unsigned int setPacketType()
{

}

unsigned int setContentLength()
{

}
