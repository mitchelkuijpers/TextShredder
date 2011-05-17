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
};

#endif // CLIENT_H
