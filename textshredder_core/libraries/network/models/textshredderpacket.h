#ifndef TEXTSHREDDERPACKET_H
#define TEXTSHREDDERPACKET_H

#include <QObject>
#include "textshredderheader.h"


#define kPacketTypeEdits 1
#define kPacketTypeFileRequest 2
#define kPacketTypeFileData 3
#define kPacketTypeSetAlias 4
#define kPacketTypeAvailableFiles 5


class TextShredderPacket : public QObject
{
    Q_OBJECT
public:
	/**
	  * Default constructor.
	  */
	TextShredderPacket( QObject * );

	TextShredderPacket(QObject *parent, unsigned char packetType);

	/**
	  * Constructor that will initialize a TextShredderPacket with a given
	  * TextShredderHeader and content.
	  *
	  * @param the header.
	  * @param the content.
	  */
	TextShredderPacket( QObject *, TextShredderHeader &, QByteArray & );

	/**
	  * Constructor which makes an TextShredderPacket with
	  */
	TextShredderPacket( QObject *, unsigned char, QByteArray & );

	/**
	  * Copy constructor
	  */
	TextShredderPacket(TextShredderPacket & otherPacket);

	/**
	  * Returns if the packet represents an packet containing edits.
	  */
    bool isEditPacket();

	/**
	  * Returns if the packet represents an packet containing a file request.
	  */
	bool isFileRequestPacket();

	/**
	  * Returns if the packet represents an packet containing file data.
	  */
	bool isFileDataPacket();

	/**
	  * Returns if the packet represents an packet containing file data.
	  */
	bool isSetAliasPacket();

	bool isSyncableFilesPacket();
	bool isIncomplete();

	void appendContentData(QByteArray & data);

	unsigned int length();
	unsigned int numberOfBytesNeeded();

	TextShredderPacket & operator=(TextShredderPacket & otherPacket);

	bool operator==(TextShredderPacket & otherPacket);

	//Setters
	void setContent(QByteArray &bytes);

	//Getters
	QByteArray & getContent();
	TextShredderHeader & getHeader();

signals:

public slots:

private:
	TextShredderHeader header;
	QByteArray content;
};

#endif // TEXTSHREDDERPACKET_H
