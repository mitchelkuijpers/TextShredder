#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

bool Client::connectToServer(QHostAddress &addr, quint16 port)
{
	return true;
}


