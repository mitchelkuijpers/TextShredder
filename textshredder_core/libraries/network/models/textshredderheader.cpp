#include "textshredderheader.h"

TextShredderHeader::TextShredderHeader( QObject *parent ) :
                                        QObject(parent),
                                        protocolVersion(kProtocolVersion),
                                        contentLength(0),
										packetType(0),
										connectionHandle(0)
{

}

TextShredderHeader::TextShredderHeader( QObject *parent,
										unsigned char protocolVersion,
										unsigned int contentLength,
										unsigned char packetType,
										unsigned int connectionHandle) :
		QObject(parent), protocolVersion(protocolVersion), contentLength(contentLength),
		packetType(packetType), connectionHandle(connectionHandle)
{
}

TextShredderHeader::TextShredderHeader( QObject *parent ,
                                        const QByteArray &buffer ) :
QObject(parent)
{
	int offset = 0;

	protocolVersion = buffer[offset];
	offset += sizeof(protocolVersion);

	memcpy(&contentLength, (const void *) &(buffer.data()[offset]), sizeof(unsigned int));
	offset += sizeof(contentLength);

	packetType = buffer[offset];
	offset += sizeof(packetType);

	memcpy(&connectionHandle, (const void *) &(buffer.data()[offset]), sizeof(unsigned int));
	offset += sizeof(connectionHandle);
}

TextShredderHeader::TextShredderHeader(const TextShredderHeader & other)
	: QObject(other.parent())
{
	this->contentLength = other.contentLength;
	this->packetType = other.packetType;
	this->protocolVersion = other.protocolVersion;
	this->connectionHandle = other.connectionHandle;
}

TextShredderHeader & TextShredderHeader::operator=(const TextShredderHeader & other)
{
	this->contentLength = other.contentLength;
	this->packetType = other.packetType;
	this->protocolVersion = other.protocolVersion;
	this->connectionHandle = other.connectionHandle;
	return *this;
}

bool TextShredderHeader::operator==(const TextShredderHeader & other)
{
	if (this->contentLength == other.contentLength &&
		this->packetType == other.packetType &&
		this->protocolVersion == other.protocolVersion &&
		this->connectionHandle == other.connectionHandle) {
		return true;
	}
	return false;
}


void TextShredderHeader::appendToQByteArray( QByteArray &buffer )
{
    buffer.append( protocolVersion );
    buffer.append( (const char *)&contentLength, (int) sizeof(unsigned int) );
    buffer.append( packetType );
	buffer.append( (const char *)&connectionHandle, (int) sizeof(unsigned int) );
}

unsigned char TextShredderHeader::getProtocolVersion()
{
    return protocolVersion;
}

unsigned char TextShredderHeader::getPacketType()
{
    return packetType;
}

unsigned int TextShredderHeader::getContentLength()
{
    return contentLength;
}

unsigned int TextShredderHeader::getConnectionHandle()
{
	return connectionHandle;
}

void TextShredderHeader::setProtocolVersion( unsigned char newValue )
{
    protocolVersion = newValue;
}

void TextShredderHeader::setContentLength( unsigned int newValue )
{
    contentLength = newValue;
}

void TextShredderHeader::setPacketType( unsigned char newValue )
{
    packetType = newValue;
}

void TextShredderHeader::setConnectionHandle( unsigned int newValue )
{
	connectionHandle = newValue;
}

