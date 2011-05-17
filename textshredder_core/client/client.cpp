#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

bool Client::connectToServer(QHostAddress &addr, quint16 port)
{
	qDebug("A");
	connection = new TextShredderConnection(this, addr, port);
	qDebug("B");
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(connectionDidEncounterEnd()));

	qDebug("C");
	connect(connection, SIGNAL(statusChanged(TextShredderConnectionStatus)), this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
	qDebug("D");
	return true;
}

void Client::connectionStatusChanged(TextShredderConnectionStatus status)
{
	if (status == Connected) {
		emit clientConnected();
	}
}

void Client::connectionDidEncounterEnd()
{

}
