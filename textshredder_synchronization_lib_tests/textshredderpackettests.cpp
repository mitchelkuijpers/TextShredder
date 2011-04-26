#include "textshredderpackettests.h"
#include "../textshredder_synchronization_lib/textshredderpacket.h"

void TextShredderPacketTests::testCreatingBlankPacket()
{
	TextShredderPacket *newPacket = new TextShredderPacket(this);

	QVERIFY2(newPacket != NULL, "TextShredderPacket should not be initialized as null");
	QVERIFY2(newPacket->getContent().isEmpty(), "TextShredderPacket should not be initialized with a content length");
}

void TextShredderPacketTests::testCreatingPacketWithHeaderAndContent()
{
	TextShredderHeader header(this);
	QByteArray content;
	TextShredderPacket *newPacket = new TextShredderPacket(this, header, content);

	QVERIFY2(newPacket != NULL, "TextShredderPacket should not be initialized as null");
	QVERIFY2(newPacket->getContent() == content, "TextShredderPacket should not be initialized with the content");
	QVERIFY2(newPacket->getHeader() == header, "TextShredderPacket should be initialized with the header");

	delete newPacket;
}

void TextShredderPacketTests::testCreatingPacketWithTypeAndContent()
{
	QByteArray content;
	TextShredderPacket *newPacket = new TextShredderPacket(this, kPacketTypeEdits, content);

	QVERIFY2( newPacket != NULL, "TextShredderPacket should not be initialized as null");
	QVERIFY2( newPacket->getContent() == content, "TextShredderPacket should be initialized with the content");
	QVERIFY2( newPacket->isEditPacket() ,"TextShredderPacket should be a edit packet");

	delete newPacket;
}

void TextShredderPacketTests::testCheckingOnEditPacket()
{
	QByteArray content;
	TextShredderPacket *editPacket = new TextShredderPacket(this, kPacketTypeEdits, content);
	TextShredderPacket *notEditPacket = new TextShredderPacket(this, kPacketTypeEdits + 1, content);

	QVERIFY2( editPacket->isEditPacket() == true, "TextShredderPacket should be an edit packet");
	QVERIFY2( notEditPacket->isEditPacket() == false, "TextShredderPacket should not be an edit packet");

	delete editPacket;
	delete notEditPacket;
}


