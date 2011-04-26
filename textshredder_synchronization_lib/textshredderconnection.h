#ifndef TEXTSHREDDERCONNECTION_H
#define TEXTSHREDDERCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QTextStream>
#include <QTextOStream>
#include <QHostAddress>
#include "textshredderpacket.h"
#include "textshredderpacketparser.h"

typedef enum {
	Disconnected,
	Error,
	Neutral
} TextShredderConnectionStatus;

class TextShredderConnection : public QObject
{
    Q_OBJECT
public:
	TextShredderConnection(QObject *parent, int socketDescriptor);
	TextShredderConnection(QObject *parent, QString &hostName, int port);
	QString getPeerAdress();

private:
	QTcpSocket socket;
	QList<TextShredderPacket> queue;


	TextShredderConnectionStatus status;
signals:
	void statusChanged(TextShredderConnectionStatus);
	void queueChanged();
	void newIncomingPacket(TextShredderPacket &packet);

public slots:
	void read();
	void write(TextShredderPacket &);
	void socketStateChanged(QAbstractSocket::SocketState);
	void socketError(QAbstractSocket::SocketError);
};
#endif // TEXTSHREDDERCONNECTION_H
