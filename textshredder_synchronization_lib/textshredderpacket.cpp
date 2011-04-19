#include "textshredderpacket.h"

TextShredderPacket::TextShredderPacket( QObject *parent ) :
	QObject(parent), header(NULL)
{
	header = new TextShredderHeader( this );
}

TextShredderPacket::TextShredderPacket(QObject *parent,
									   TextShredderHeader * header, QByteArray & content) :
    QObject(parent), header(header), content(content)
{
}

TextShredderPacket::TextShredderPacket( QObject *parent,
										unsigned char packetType,
										QByteArray & content) :
	QObject(parent), header(NULL), content(content)
{
	header = new TextShredderHeader(this, kProtocolVersion, content.size(), packetType);
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
	return header->getPacketType() == kPacketTypeEdits;
}

QByteArray & TextShredderPacket::getContent() {
	return content;
}

TextShredderHeader * TextShredderPacket::getHeader() {
	return header;
}
