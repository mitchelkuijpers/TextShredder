#ifndef TEXTSHREDDERCONNECTION_H
#define TEXTSHREDDERCONNECTION_H

#include <QtCore>
#include <QtGlobal>
#include <QTcpSocket>
#include <QList>
#include <QTextStream>
#include <QTextOStream>
#include <QHostAddress>
#include "models/textshredderpacket.h"
#include "textshredderpacketparser.h"
#include <QTcpServer>

typedef enum {
	Disconnected = 0,
	HostLookup = 1,
	Establishing = 2,
	Connected = 3,
	Bound = 4,
	Closing = 5,
	Error = 6,
	Neutral =7
} TextShredderConnectionStatus;

class TextShredderConnection : public QObject
{
    Q_OBJECT
public:
	/**
	 * Constructor which sets up the connection, with the given socket and sets its status to neutral
	 */
	TextShredderConnection(QObject *parent, int socketDescriptor);
	/**
	 * Constructor which sets the param variables
	 */
	TextShredderConnection(QObject *parent, QString &hostName, int port, bool startImmediately = true);
	/**
	 * Gets the ipaddress of the client on the connected socket.
	 * @return The ipaddress of the client on the connected socket.
	 */
	QString getPeerAdress();
	/**
	 * Gets the port of the client on the connected socket.
	 * @return The port which the connection listens on
	 */
	unsigned int getPort();
	/**
	 * Connects the client on the given socket
	 */
	void startConnection();
	/**
	 * Destructor
	 */
	~TextShredderConnection();
private:
	QSharedPointer <QTcpSocket> socket;
	QList<TextShredderPacket> queue;
	TextShredderConnectionStatus status;
	TextShredderPacketParser parser;
	unsigned int port;
	QString hostAddressString;

	/**
	 * Sets up all the correct signals for the socket
	 */
	void setupSignalsForSocket();
	/**
	 * Breaks down all the correct signals for the socket
	 */
	void breakDownSignalsForSocket();
	/**
	 * Sends the right emit according to the packettype
	 * @param &packet The packet which holds the type
	 */
	void emitNewIncomingPacket(TextShredderPacket &packet);

signals:
	void socketConnectedSuccessfully();
	void socketErrorReceived(QAbstractSocket::SocketError);

	void queueChanged();
	void clientDisconnected();

	//Incoming packet signals
	void incomingSetAliasPacketContent(QByteArray &content);
	void incomingFileRequestPacket(TextShredderPacket &content);
	void incomingFileDataPacket(TextShredderPacket& content, quint16 destinationHandle);
	void incomingEditPacketContent(QByteArray &content, quint16 destinationHandle);
	void incomingSyncableFilesPacket(QByteArray &content);
	void incomingEndSynchronizationPacket(quint16 destinationHandle);
	void incomingOnlineUsersPacket(TextShredderPacket &packet);

public slots:
	void read();
	void write(TextShredderPacket &);
	void socketStateChanged(QAbstractSocket::SocketState);
	void socketError(QAbstractSocket::SocketError);
	void clientHasDisconnected();
	void sendPacket(TextShredderPacket &);
};
#endif // TEXTSHREDDERCONNECTION_H
