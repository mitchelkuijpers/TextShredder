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

typedef enum {
	Disconnected,
	HostLookup,
	Establishing,
	Connected,
	Bound,
	Closing,
	Error,
	Neutral
} TextShredderConnectionStatus;

class TextShredderConnection : public QObject
{
    Q_OBJECT
public:
	TextShredderConnection(QObject *parent);
	TextShredderConnection(QObject *parent, int socketDescriptor);
	TextShredderConnection(QObject *parent, QString &hostName, int port);
	QString getPeerAdress();
	unsigned int getPort();

	quint16 getLocalPort();

private:
	QTcpSocket socket;
	QList<TextShredderPacket> queue;
	TextShredderConnectionStatus status;
	TextShredderPacketParser parser;
	unsigned int port;
	void setupSignalsForSocket();
	void emitNewIncomingPacket(TextShredderPacket &packet);
	void handleFileRequestPacket(TextShredderPacket &packet);

signals:
	void statusChanged(TextShredderConnectionStatus);
	void queueChanged();
	void clientDisconnected();

	//Incoming packet signals
	void incomingSetAliasPacketContent(QByteArray &content);
	void incomingFileDataPacketContent(QByteArray &content);
	void incomingEditPacketContent(QByteArray &content);

public slots:
	void read();
	void write(TextShredderPacket &);
	void socketStateChanged(QAbstractSocket::SocketState);
	void socketError(QAbstractSocket::SocketError);
	void clientHasDisconnected();
	void sendPacket(TextShredderPacket &);

};
#endif // TEXTSHREDDERCONNECTION_H
