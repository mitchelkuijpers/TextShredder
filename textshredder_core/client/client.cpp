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
	connect(connection, SIGNAL(statusChanged(TextShredderConnectionStatus, QAbstractSocket::SocketError)),
			this, SLOT(connectionStatusChanged(TextShredderConnectionStatus, QAbstractSocket::SocketError)));
	connect(connection, SIGNAL(incomingSyncableFilesPacket(QByteArray&)),
			FileManager::Instance(), SLOT(handleReceivedSyncableFiles(QByteArray &)));
	connection->startConnection();
	return true;
}

void Client::connectionStatusChanged(TextShredderConnectionStatus status, QAbstractSocket::SocketError error )
{
	if (status == Connected) {
		emit clientConnected();

	} else if (status == Error) {
		emit clientConnectionError(error);
	}
}

void Client::connectionDidEncounterEnd()
{

}
