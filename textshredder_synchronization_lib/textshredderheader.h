#ifndef TEXTSHREDDERHEADER_H
#define TEXTSHREDDERHEADER_H

#define kProtocolVersion 1

#define kPacketTypeEdits 0
#define kPacketTypeFileData 1
#define kPacketTypeFileRequest 2

#define kHeaderLength 6

class TextShredderHeader
{
public:
    TextShredderHeader();
    TextShredderHeader(char protocolVersion, int contentLength, char packetType);

    void writeInBuffer( char * );
    static TextShredderHeader * headerFromBuffer( char * );

    char getProtocolVersion();

    int getPacketType();

    int getContentLength();

private:
    char protocolVersion;
    int contentLength;
    char packetType;
};

#endif // TEXTSHREDDERHEADER_H
