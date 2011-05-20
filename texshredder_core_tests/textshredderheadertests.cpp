#include "textshredderheadertests.h"
#include "../textshredder_core/libraries/network/models/textshredderheader.h"

void TextShredderHeaderTests::testEmptyHeaderCreation()
{
    TextShredderHeader * newTextShredder = new TextShredderHeader(this);

    QVERIFY2(newTextShredder != NULL, "Failed creating TSH object.");
    QVERIFY2(newTextShredder->getProtocolVersion() == kProtocolVersion, "Failed protocol test");
    QVERIFY2(newTextShredder->getContentLength() == 0, "Failed content length: non-zero");
    QVERIFY2(newTextShredder->getPacketType() == 0, "Failed packet type: non-zero");
}

void TextShredderHeaderTests::testHeaderCreationWihParameters()
{
    unsigned char protocolVersion = 6;
    unsigned int contentLength = 900;
    unsigned char contentType = 2;

    TextShredderHeader * newTextShredder = new TextShredderHeader(this, protocolVersion, contentLength, contentType);

    QVERIFY2(newTextShredder != NULL, "Failed creating TSH object.");
    QVERIFY2(newTextShredder->getProtocolVersion() == protocolVersion, "Failed protocol test, value has to be " + protocolVersion);
    QVERIFY2(newTextShredder->getContentLength() == contentLength, "Failed content length, value has to be " + contentLength);
    QVERIFY2(newTextShredder->getPacketType() == contentType, "Failed packet type has to be " + contentType);
}

void TextShredderHeaderTests::testHeaderCreationFromQByteArray() {
    QByteArray byteArray;
    unsigned int contentLength = 1000000004;
    unsigned char packetType = 4;
    unsigned char protocolVersion = 5;

    unsigned char buffer[6];
    buffer[0] = protocolVersion;
    memcpy(&(buffer[1]), &contentLength, sizeof(unsigned int));
    buffer[5] = packetType;

    byteArray.append( (const char *)buffer, 6);

    TextShredderHeader *newTextShredderHeader = new TextShredderHeader(this, byteArray);
    QVERIFY2(newTextShredderHeader != NULL, "Failed to create TextShredderHeader from buffer");
    QVERIFY2(newTextShredderHeader->getProtocolVersion() == protocolVersion, "Failed to create TextShredderHeader from buffer");
    QVERIFY2(newTextShredderHeader->getContentLength() == contentLength, "Failed to create TextShredderHeader from buffer");
    QVERIFY2(newTextShredderHeader->getPacketType() == packetType, "Failed to create TextShredderHeader from buffer");
}

void TextShredderHeaderTests::testHeaderWriteToQByteArray()
{
    unsigned int contentLength = 256;
    unsigned char packetType = 4;
    unsigned char protocolVersion = 5;

    unsigned int bufferContentLength;
    unsigned char bufferPacketType;
    unsigned char bufferProtocolVersion;

    QByteArray byteBuffer;

    TextShredderHeader * newTextShredderHeader = new TextShredderHeader(this, protocolVersion, contentLength, packetType);
    newTextShredderHeader->appendToQByteArray(byteBuffer);

    bufferProtocolVersion = byteBuffer[0];
    memcpy(&bufferContentLength, &(byteBuffer.data()[1]), sizeof(unsigned int));
    bufferPacketType = byteBuffer[5];

    QVERIFY2(bufferContentLength == contentLength, "Failed to write contentLength from TextShredderHeader to buffer");
    QVERIFY2(bufferPacketType == packetType, "Failed to write packetType from TextShredderHeader to buffer");
    QVERIFY2(bufferProtocolVersion == protocolVersion, "Failed to write protocolVersion from TextShredderHeader to buffer");
}

void TextShredderHeaderTests::testHeaderSerializationAndDeserialization() {
        QByteArray byteArray;
        TextShredderHeader *firstHeader = new TextShredderHeader(this, 100, 800, 200);
        firstHeader->appendToQByteArray (byteArray);
        TextShredderHeader *secondHeader = new TextShredderHeader(this, byteArray);

        QVERIFY2(firstHeader->getContentLength() == secondHeader->getContentLength(),
                         "Failed to write and parse TextShredderHeader to and from buffer");
        QVERIFY2(firstHeader->getContentLength() == secondHeader->getContentLength(),
                         "Failed to write and parse TextShredderHeader to and from buffer");
        QVERIFY2(firstHeader->getContentLength() == secondHeader->getContentLength(),
                         "Failed to write and parse TextShredderHeader to and from buffer");
}