#include "textshredderpacket.h"

TextShredderPacket::TextShredderPacket( QObject *parent ) :
	QObject(parent), header(NULL)
{
}

TextShredderPacket::TextShredderPacket(QObject *parent,
									   unsigned char packetType) :
	QObject(parent), header(this, packetType, 0, packetType)
{
}
TextShredderPacket::TextShredderPacket(QObject *parent,
									   TextShredderHeader & header, QByteArray & content) :
    QObject(parent), header(header), content(content)
{
}

TextShredderPacket::TextShredderPacket( QObject *parent,
										unsigned char packetType,
										QByteArray & content) :
	QObject(parent), header(NULL, kProtocolVersion, content.size (), packetType), content(content)
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
