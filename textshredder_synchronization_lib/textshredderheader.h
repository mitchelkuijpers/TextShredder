#ifndef TEXTSHREDDERHEADER_H
#define TEXTSHREDDERHEADER_H

#include <QtCore/QtCore>

#define kProtocolVersion 1

#define kPacketTypeEdits 0
#define kPacketTypeFileData 1
#define kPacketTypeFileRequest 2

#define kHeaderLength 6

class TextShredderHeader : QObject
{
public:

    /**
     * Default constructor which makes a TextShredderHeader
     * object with a protocolVersion set to kProtocolVersion
     * and other values set to 0
     */
    TextShredderHeader();

    /**
     * TextShredderHeader constructor which makes an object which properties
     * are set to the given parameters.
     *
     * @param the headers protocolVersion.
     * @param the length of the body the header precedes.
     * @param the type of content representation which the heades is
                            followed by.
     */
    TextShredderHeader( unsigned char protocolVersion,
                        unsigned int contentLength,
                        unsigned char packetType );

    /**
     * TextShredderHeader coonstructor which makes an header based
     * on bytes stored in a QByteArray
     *
     * @param the byte array on which the header will be based on.
     */
    TextShredderHeader( const QByteArray & );

    /**
     * Function to make a byte array representation of a TextShredderHeader
     *
     * @param the byte array in which the byte representation is stored.
     */
    void appendToQByteArray( QByteArray & );

    /* Getters */
    unsigned char getProtocolVersion();
    unsigned int getPacketType();
    unsigned int getContentLength();

    /* Setters */
    unsigned char setProtocolVersion();
    unsigned int setPacketType();
    unsigned int setContentLength();

private:
    unsigned char protocolVersion;
    unsigned int contentLength;
    unsigned char packetType;
};

#endif // TEXTSHREDDERHEADER_H
