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
	//if ( content == NULL ) {
	//	throw QString("TextShredderPacket cannot be initialized with NULL content");
	//}

	header = new TextShredderHeader(this, kProtocolVersion, content.size(), packetType);
}

TextShredderPacket & TextShredderPacket::operator=(TextShredderPacket & otherPacket)
{
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
