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
#include "connectionlistener.h"

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
	TextShredderConnection(QObject *parent);
	TextShredderConnection(QObject *parent, int socketDescriptor);
	TextShredderConnection(QObject *parent, QString &hostName, int port, bool startImmediately = true);
	QString getPeerAdress();
	unsigned int getPort();

	quint16 getLocalPort();
	void startConnection();

private:
	QSharedPointer<ConnectionListener> connectionListener;
	QTcpSocket socket;
	QList<TextShredderPacket> queue;
	TextShredderConnectionStatus status;
	TextShredderPacketParser parser;
	unsigned int port;
	QString hostAddressString;

	void setupSignalsForSocket();
	void breakDownSignalsForSocket();

	void emitNewIncomingPacket(TextShredderPacket &packet);
	void handleFileRequestPacket(TextShredderPacket &packet);

signals:
	void statusChanged(TextShredderConnectionStatus, QAbstractSocket::SocketError);
	void queueChanged();
	void clientDisconnected();

	//Incoming packet signals
	void incomingSetAliasPacketContent(QByteArray &content);
	void incomingFileDataPacketContent(QByteArray &content);
	void incomingEditPacketContent(QByteArray &content);
	void incomingSyncableFilesPacket(QByteArray &content);

public slots:
	void read();
	void write(TextShredderPacket &);
	void socketStateChanged(QAbstractSocket::SocketState);
	void socketError(QAbstractSocket::SocketError);
	void clientHasDisconnected();
	void sendPacket(TextShredderPacket &);

	void deleteServer(ConnectionListener *obj);
	void socketDescriptorReady(quint16 socketDescriptor);
};
#endif // TEXTSHREDDERCONNECTION_H
