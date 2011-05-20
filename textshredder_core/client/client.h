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
	void availableFilesRequest();
	void clientConnectionError();

private slots:
	void connectionDidEncounterEnd();
	void connectionStatusChanged(TextShredderConnectionStatus status);
};

#endif // CLIENT_H
