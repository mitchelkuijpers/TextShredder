#include "textshredderpacketparsertests.h"
#include <QString>
#include <QDebug>

void TextShredderPacketParserTests::testWrongPacket()
{
	QByteArray bytes;
	bytes.append((char)0, (int )sizeof(unsigned char));
	bool throwed = false;
	try {
		TextShredderPacketParser::makeAllocatedPacketFromBytes(&bytes);
	} catch (QString error) {
		throwed = true;
	}
	QVERIFY2(throwed, "it should throw a qString");
}

void TextShredderPacketParserTests::testPacket()
{
	QByteArray tempContent("this is some test content");
	unsigned char version = (unsigned char)kProtocolVersion;
	unsigned char type = (unsigned char)kPacketTypeEdits;
	unsigned int size = (unsigned int)tempContent.size();

	char buffer[kHeaderLength];
	buffer[0] = version;
	memcpy(&buffer[1], &size, sizeof(unsigned int));
	buffer[5] = type;

	QByteArray packet((const char *)buffer, kHeaderLength);
	packet.append(tempContent.data());

	TextShredderPacket *tsPacket = TextShredderPacketParser::makeAllocatedPacketFromBytes(&packet);

	QVERIFY2(tsPacket->isEditPacket(), "Should be and edit packet..");

	QByteArray content(tsPacket->getContent());
	QVERIFY2(content == tempContent, "Content was not the same");

}



