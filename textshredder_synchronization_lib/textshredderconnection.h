#ifndef TEXTSHREDDERCONNECTION_H
#define TEXTSHREDDERCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QTextStream>
#include <QTextOStream>
#include "textshredderpacket.h"
#include "textshredderpacketparser.h"

class TextShredderConnection : public QObject
{
    Q_OBJECT
public:
	explicit TextShredderConnection(QObject *parent, int socketDescriptor);

private:
	QTcpSocket socket;
	QList<TextShredderPacket> queue;

	enum TextShredderConnectionStatus{
		Disconnected,
		Error,
		Neutral
	};
	TextShredderConnectionStatus status;
signals:
	void statusChanged(TextShredderConnectionStatus);
	void queueChanged();
	void newIncomingPacket(TextShredderPacket * packet);

public slots:

private slots:
	void read();
	void write(TextShredderPacket);
	void socketStateChanged(QAbstractSocket::SocketState);
	void socketError(QAbstractSocket::SocketError);
};
#endif // TEXTSHREDDERCONNECTION_H
