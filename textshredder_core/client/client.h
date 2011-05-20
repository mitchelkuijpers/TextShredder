#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include "../libraries/network/textshredderconnection.h"

class Client : public QObject
{
    Q_OBJECT
public:
	Client(QObject *parent);

	bool connectToServer(QHostAddress &addr, quint16 port);

private:
	TextShredderConnection *connection;

signals:
	void clientConnected();
	void clientConnectionError(QAbstractSocket::SocketError);
	void availableFilesRequest();

private slots:
	void connectionDidEncounterEnd();
	void connectionStatusChanged(TextShredderConnectionStatus status, QAbstractSocket::SocketError error );
};

#endif // CLIENT_H
