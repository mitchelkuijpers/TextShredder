#include "textshredderpacket.h"

TextShredderPacket::TextShredderPacket( QObject *parent ) :
	QObject(parent), header(NULL)
{
}

TextShredderPacket::TextShredderPacket(QObject *parent,
									   unsigned char packetType, unsigned int destination ) :
	QObject(parent), header(this, kProtocolVersion, 0, packetType, destination)
{
}
TextShredderPacket::TextShredderPacket(QObject *parent,
									   TextShredderHeader & header, QByteArray & content) :
    QObject(parent), header(header), content(content)
{
}

TextShredderPacket::TextShredderPacket( QObject *parent,
										unsigned char packetType,
										QByteArray & content, unsigned int destination ) :
	QObject(parent), header(NULL, kProtocolVersion, content.size (), packetType, destination), content(content)
{
}

TextShredderPacket::TextShredderPacket(TextShredderPacket & otherPacket)
	: QObject(NULL), header(otherPacket.getHeader()), content(otherPacket.getContent())
{
}


TextShredderPacket & TextShredderPacket::operator=(TextShredderPacket & otherPacket)
{
	this->header = otherPacket.header;
	this->content = otherPacket.content;
	return *this;
}

bool TextShredderPacket::isEditPacket()
{
	return header.getPacketType() == kPacketTypeEdits;
}

bool TextShredderPacket::isFileDataPacket ()
{
	return (header.getPacketType() == kPacketTypeFileData);
}

bool TextShredderPacket::isFileRequestPacket()
{
	return (header.getPacketType() == kPacketTypeFileRequest);
}

bool TextShredderPacket::isSetAliasPacket()
{
	return (header.getPacketType() == kPacketTypeSetAlias);
}

bool TextShredderPacket::isSyncableFilesPacket()
{
	return (header.getPacketType()) == kPacketTypeAvailableFiles;
}

void TextShredderPacket::setContent(QByteArray &bytes)
{
	content = bytes;
	header.setContentLength((unsigned int)bytes.length());
}

QByteArray & TextShredderPacket::getContent()
{
	return content;
}

TextShredderHeader & TextShredderPacket::getHeader() {
	return header;
}

void TextShredderPacket::appendContentData(QByteArray &data)
{
	this->content.append(data);
}

unsigned int TextShredderPacket::numberOfBytesNeeded()
{
	unsigned int currentSize = this->content.length();
	unsigned int expectedSize = this->getHeader().getContentLength();
	if (expectedSize > currentSize) {
		return expectedSize - currentSize;
	}
	return 0;
}

bool TextShredderPacket::isIncomplete()
{
	return (this->getHeader().getContentLength() > (unsigned int) this->content.length());

}

unsigned int TextShredderPacket::length()
{
	return kHeaderLength + this->content.length();
}

bool TextShredderPacket::operator ==(TextShredderPacket &otherPacket)
{
	return (this->getContent() == otherPacket.getContent() && this->getHeader() == otherPacket.getHeader());
}
