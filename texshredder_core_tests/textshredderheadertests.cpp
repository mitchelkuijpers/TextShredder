#include "textshredderheadertests.h"
#include "../textshredder_core/libraries/network/models/textshredderheader.h"

void TextShredderHeaderTests::testEmptyHeaderCreation()
{
    TextShredderHeader * newTextShredder = new TextShredderHeader(this);

    QVERIFY2(newTextShredder != NULL, "Failed creating TSH object.");
    QVERIFY2(newTextShredder->getProtocolVersion() == kProtocolVersion, "Failed protocol test");
    QVERIFY2(newTextShredder->getContentLength() == 0, "Failed content length: non-zero");
    QVERIFY2(newTextShredder->getPacketType() == 0, "Failed packet type: non-zero");
	QVERIFY2(newTextShredder->getConnectionHandle() == 0, "Failed Connection Handle: non-zero");
}

void TextShredderHeaderTests::testHeaderCreationWihParameters()
{
    unsigned char protocolVersion = 6;
    unsigned int contentLength = 900;
    unsigned char contentType = 2;
	unsigned int connectionHandle = 5;

	TextShredderHeader * firstHeader = new TextShredderHeader(this, protocolVersion, contentLength, contentType);

	QVERIFY2(firstHeader != NULL, "Failed creating TSH object.");
	QVERIFY2(firstHeader->getProtocolVersion() == protocolVersion, "Failed protocol test, value has to be " + protocolVersion);
	QVERIFY2(firstHeader->getContentLength() == contentLength, "Failed content length, value has to be " + contentLength);
	QVERIFY2(firstHeader->getPacketType() == contentType, "Failed packet type has to be " + contentType);
	QVERIFY2(firstHeader->getConnectionHandle() == 0, "Failed Connection Handle: non-zero");

	TextShredderHeader * secondHeader =
			new TextShredderHeader(this, protocolVersion, contentLength,
								   contentType, connectionHandle);

	QVERIFY2(secondHeader != NULL, "Failed creating TSH object.");
	QVERIFY2(secondHeader->getProtocolVersion() == protocolVersion, "Failed protocol test, value has to be " + protocolVersion);
	QVERIFY2(secondHeader->getContentLength() == contentLength, "Failed content length, value has to be " + contentLength);
	QVERIFY2(secondHeader->getPacketType() == contentType, "Failed packet type has to be " + contentType);
	QVERIFY2(secondHeader->getConnectionHandle() == connectionHandle, "Failed, Connection Handle has to be " + connectionHandle);
}

void TextShredderHeaderTests::testHeaderCreationFromQByteArray() {
    QByteArray byteArray;
    unsigned int contentLength = 1000000004;
    unsigned char packetType = 4;
    unsigned char protocolVersion = 5;
	unsigned int  connectionHandle = 6;

	unsigned char buffer[kHeaderLength];
    buffer[0] = protocolVersion;
    memcpy(&(buffer[1]), &contentLength, sizeof(unsigned int));
    buffer[5] = packetType;
	memcpy(&(buffer[6]), &connectionHandle, sizeof(unsigned int));

	byteArray.append( (const char *)buffer, kHeaderLength);

    TextShredderHeader *newTextShredderHeader = new TextShredderHeader(this, byteArray);
    QVERIFY2(newTextShredderHeader != NULL, "Failed to create TextShredderHeader from buffer");
	QVERIFY2(newTextShredderHeader->getProtocolVersion() == protocolVersion, "Failed to create TextShredderHeader from buffer (protocol)");
	QVERIFY2(newTextShredderHeader->getContentLength() == contentLength, "Failed to create TextShredderHeader from buffer (contentLength)");
	QVERIFY2(newTextShredderHeader->getPacketType() == packetType, "Failed to create TextShredderHeader from buffer (packetType)");
	QVERIFY2(newTextShredderHeader->getConnectionHandle() == connectionHandle, "Failed to create TextShredderHeader from buffer (connectionHandle)");
}

void TextShredderHeaderTests::testHeaderWriteToQByteArray()
{
    unsigned int contentLength = 256;
    unsigned char packetType = 4;
    unsigned char protocolVersion = 5;
	unsigned int connectionHandle = 6;

    unsigned int bufferContentLength;
    unsigned char bufferPacketType;
    unsigned char bufferProtocolVersion;
	unsigned int bufferConnectionHandle;
    QByteArray byteBuffer;

	TextShredderHeader * newTextShredderHeader = new TextShredderHeader(this, protocolVersion, contentLength, packetType, connectionHandle);
    newTextShredderHeader->appendToQByteArray(byteBuffer);

    bufferProtocolVersion = byteBuffer[0];
    memcpy(&bufferContentLength, &(byteBuffer.data()[1]), sizeof(unsigned int));
    bufferPacketType = byteBuffer[5];
	memcpy(&bufferConnectionHandle, &(byteBuffer.data()[6]), sizeof(unsigned int));

    QVERIFY2(bufferContentLength == contentLength, "Failed to write contentLength from TextShredderHeader to buffer");
    QVERIFY2(bufferPacketType == packetType, "Failed to write packetType from TextShredderHeader to buffer");
    QVERIFY2(bufferProtocolVersion == protocolVersion, "Failed to write protocolVersion from TextShredderHeader to buffer");
	QVERIFY2(bufferConnectionHandle == connectionHandle, "Failed to write connectionHandle from TextShredderHeader to buffer");
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
