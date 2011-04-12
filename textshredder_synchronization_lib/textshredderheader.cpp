#include "textshredderheader.h"

TextShredderHeader::TextShredderHeader() :
        protocolVersion(kProtocolVersion), contentLength(0), packetType(0)
{

}

TextShredderHeader::TextShredderHeader(char protocolVersion, int contentLength, char packetType) :
        protocolVersion(protocolVersion), contentLength(contentLength), packetType(packetType)
{
}

void TextShredderHeader::writeInBuffer( char * buffer ) {
    int offset = 0;

    buffer[offset] = protocolVersion;
    offset += sizeof(protocolVersion);

    buffer[offset] = contentLength;
    offset += sizeof(contentLength);

    buffer[offset] = packetType;
}

static TextShredderHeader * headerFromBuffer( char * buffer ) {
    int offset = 0;

    int protocolVersion(buffer[offset]);
    offset += sizeof(protocolVersion);

    int contentLength = (int) buffer[offset];
    offset += sizeof(contentLength);

    int packetType = buffer[offset];

    return new TextShredderHeader(protocolVersion, contentLength, packetType);
}

char TextShredderHeader::getProtocolVersion() {
    return protocolVersion;
}

int TextShredderHeader::getPacketType() {
    return packetType;
}

int TextShredderHeader::getContentLength() {
    return contentLength;
}
