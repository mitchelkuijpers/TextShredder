#include "client.h"
#include "../libraries/synchronization/filemanager.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

bool Client::connectToServer(QHostAddress &addr, quint16 port)
{
	QString addrString = addr.toString();

	connection = new TextShredderConnection(this, addrString, port, false);
	connect(connection, SIGNAL(clientDisconnected()),
			this, SLOT(connectionDidEncounterEnd()));
	connect(connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
			this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
	connect(connection, SIGNAL(incomingSyncableFilesPacket(QByteArray&)),
			FileManager::Instance(), SLOT(handleReceivedSyncableFiles(QByteArray &)));
	connection->startConnection();
	return true;
}

void Client::connectionStatusChanged(TextShredderConnectionStatus status)
{
	if (status == Connected) {
		emit clientConnected();

	} else if (status == Error) {
		emit clientConnectionError();
	}
}

void Client::connectionDidEncounterEnd()
{

}
