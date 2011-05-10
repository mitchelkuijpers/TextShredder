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

void TextShredderPacketTests::testCheckingOnFileRequestPacket()
{
	QByteArray content;
	TextShredderPacket *fileRequest = new TextShredderPacket(this, kPacketTypeFileRequest, content);
	TextShredderPacket *notFileRequest = new TextShredderPacket(this, kPacketTypeFileRequest + 1, content);

	QVERIFY2(fileRequest->isFileRequestPacket() == true, "TextShredderPacket should be an filerequest packet");
	QVERIFY2(notFileRequest->isFileRequestPacket() == false, "TextShredderPacket should not be an filerequest packet");

	delete fileRequest;
	delete notFileRequest;
}

void TextShredderPacketTests::testCheckingOnFileDataPacket()
{
	QByteArray content;
	TextShredderPacket *fileData= new TextShredderPacket(this, kPacketTypeFileData, content);
	TextShredderPacket *notFileData = new TextShredderPacket(this, kPacketTypeFileData + 1, content);

	QVERIFY2(fileData->isFileDataPacket() == true, "TextShredderPacket should be an filedata packet");
	QVERIFY2(notFileData->isFileDataPacket() == false, "TextShredderPacket should not be an filedata packet");

	delete fileData;
	delete notFileData;
}

void TextShredderPacketTests::testCheckingOnSetAliasPacket()
{
	QByteArray content;
	TextShredderPacket *setAlias= new TextShredderPacket(this, kPacketTypeSetAlias, content);
	TextShredderPacket *notSetAlias = new TextShredderPacket(this, kPacketTypeSetAlias + 1, content);

	QVERIFY2(setAlias->isSetAliasPacket() == true, "TextShredderPacket should be an setAlias packet");
	QVERIFY2(notSetAlias->isSetAliasPacket() == false, "TextShredderPacket should not be an setAlias packet");

	delete setAlias;
	delete notSetAlias;
}

void TextShredderPacketTests::testAppendingData()
{
	QByteArray content;
	TextShredderPacket *dataPacket = new TextShredderPacket(this, kPacketTypeFileData, content);
	content = "A";
	dataPacket->appendContentData(content);

	QVERIFY2(dataPacket->getContent() == "A", "Content did not append correct, it contains: "+dataPacket->getContent());
	delete dataPacket;
}

void TextShredderPacketTests::testNumberOfBytesNeeded()
{
	TextShredderPacket *TSPacket;
}
