#ifndef TEXTSHREDDERPACKET_H
#define TEXTSHREDDERPACKET_H

#include <QObject>
#include "textshredderheader.h"


#define kPacketTypeEdits 1
#define kPacketTypeFileRequest 2
#define kPacketTypeFileData 3


class TextShredderPacket : public QObject
{
    Q_OBJECT
public:
	/**
	  * Default constructor.
	  */
	TextShredderPacket( QObject * );

	/**
	  * Constructor that will initialize a TextShredderPacket with a given
	  * TextShredderHeader and content.
	  *
	  * @param the header.
	  * @param the content.
	  */
	TextShredderPacket( QObject *, TextShredderHeader *, QByteArray & );

	/**
	  * Constructor which makes an TextShredderPacket with
	  */
	TextShredderPacket( QObject *, unsigned char, QByteArray & );

	TextShredderPacket(TextShredderPacket & otherPacket);

	/**
	  * Returns if the packet represents an packet containing edits.
	  */
    bool isEditPacket();

	TextShredderPacket & operator=(TextShredderPacket & otherPacket);

	//Getters
	QByteArray & getContent();
	TextShredderHeader * getHeader();

signals:

public slots:

private:
	TextShredderHeader * header;
	QByteArray content;
};

#endif // TEXTSHREDDERPACKET_H
