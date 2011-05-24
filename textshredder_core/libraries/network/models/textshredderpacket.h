#ifndef TEXTSHREDDERPACKET_H
#define TEXTSHREDDERPACKET_H

#include <QObject>
#include "textshredderheader.h"


#define kPacketTypeEdits 1
#define kPacketTypeFileRequest 2
#define kPacketTypeFileData 3
#define kPacketTypeSetAlias 4
#define kPacketTypeAvailableFiles 5
#define kPacketTypeSynchronizationEnd 6
#define kPacketTypeOnlineUsers 7

class TextShredderPacket : public QObject
{
    Q_OBJECT
public:
	/**
	  * Default constructor.
	  */
	TextShredderPacket( QObject * );

	TextShredderPacket(QObject *parent, unsigned char packetType, unsigned int destination = 0);

	/**
	  * Constructor that will initialize a TextShredderPacket with a given
	  * TextShredderHeader and content.
	  *
	  * @param the header.
	  * @param the content.
	  */
	TextShredderPacket( QObject *, TextShredderHeader &, QByteArray &);

	/**
	  * Constructor which makes an TextShredderPacket with
	  */
	TextShredderPacket( QObject *, unsigned char, QByteArray &, unsigned int = 0 );

	/**
	  * Copy constructor
	  */
	TextShredderPacket(TextShredderPacket & otherPacket);

	/**
	  * For the following methods: Returns if packet is such kind of packet.
	  */
    bool isEditPacket();
	bool isFileRequestPacket();
	bool isFileDataPacket();
	bool isEndSynchronizationPacket();
	bool isSetAliasPacket();
	bool isSyncableFilesPacket();
	bool isOnlineUsersPacket();
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
