#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

bool Client::connectToServer(QHostAddress &addr, quint16 port)
{
	QString addrString = addr.toString();

	connection = new TextShredderConnection(this, addrString, port, false);
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(connectionDidEncounterEnd()));
	connect(connection, SIGNAL(statusChanged(TextShredderConnectionStatus)), this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
	connection->startConnection();
	return true;
}

void Client::connectionStatusChanged(TextShredderConnectionStatus status)
{
	qDebug() << QString::number(status);
	if (status == Connected) {
		emit clientConnected();
	}
}

void Client::connectionDidEncounterEnd()
{

}
