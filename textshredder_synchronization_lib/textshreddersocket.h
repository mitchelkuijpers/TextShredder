#ifndef TEXTSHREDDERSOCKET_H
#define TEXTSHREDDERSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "textshredderpacketparser.h"
#include "textshredderpacket.h"
#include "textshredderheader.h"

class TextShredderSocket : public QTcpSocket
{
    Q_OBJECT
public:
	/**
	  * Create a textshredder socket, the socketDescriptor is <b> required </b>!
	  *
	  * @param stanard parent QObject
	  * @param the socketDescriptor
	  */
	TextShredderSocket(QObject *parent, int socketDescriptor);

	/**
	  * Read from the socket and return a Textshredderpacket.
	  * Make sure there is data to read, you can do that by calling
	  * waitForReadyRead(). Be sure to do that so you don't block the socket.
	  *
	  * @return The packet you received from the socket.
	  */
	TextShredderPacket * readPacket();

	/**
	  * Write to the client. This function wil make an ByteArray from a
	  * TextShredderpacket. If you wanna make sure the packet is written
	  * call waitForBytesWritten(timeOut).
	  *
	  * @param The packet to be written to the socket.
	  */
	void writePacket(TextShredderPacket * packet);
};

#endif // TEXTSHREDDERSOCKET_H
