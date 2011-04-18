#ifndef TEXTSHREDDERHEADER_H
#define TEXTSHREDDERHEADER_H

#include <QObject>

#define kProtocolVersion 1

#define kHeaderLength 6

class TextShredderHeader : QObject
{
    Q_OBJECT

public:

    explicit TextShredderHeader(QObject *parent);

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
    TextShredderHeader( QObject *parent,
                        unsigned char protocolVersion,
                        unsigned int contentLength,
                        unsigned char packetType );

    /**
     * TextShredderHeader coonstructor which makes an header based
     * on bytes stored in a QByteArray
     *
     * @param the byte array on which the header will be based on.
     */
    TextShredderHeader( QObject *parent, const QByteArray & );

    /**
     * Function to make a byte array representation of a TextShredderHeader
     *
     * @param the byte array in which the byte representation is stored.
     */
    void appendToQByteArray( QByteArray & );

    /* Getters */
    unsigned char getProtocolVersion();
    unsigned int getContentLength();
    unsigned char getPacketType();

    /* Setters */
    void setProtocolVersion( unsigned char newValue );
    void setContentLength( unsigned int newValue );
    void setPacketType( unsigned char newValue );

private:
    unsigned char protocolVersion;
    unsigned int contentLength;
    unsigned char packetType;
};

#endif // TEXTSHREDDERHEADER_H
