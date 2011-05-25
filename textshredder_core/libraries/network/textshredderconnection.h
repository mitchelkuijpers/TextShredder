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
	TextShredderConnection(QObject *parent, int socketDescriptor);
	TextShredderConnection(QObject *parent, QString &hostName, int port, bool startImmediately = true);
	QString getPeerAdress();
	unsigned int getPort();

	void startConnection();
	~TextShredderConnection();
private:
	QSharedPointer <QTcpSocket> socket;
	QList<TextShredderPacket> queue;
	TextShredderConnectionStatus status;
	TextShredderPacketParser parser;
	unsigned int port;
	QString hostAddressString;

	void setupSignalsForSocket();
	void breakDownSignalsForSocket();

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
