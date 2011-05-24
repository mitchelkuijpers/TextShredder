#include "client.h"
#include "../libraries/synchronization/filemanager.h"
#include "../libraries/network/models/setaliaspacket.h"

QSharedPointer<Client> Client::sharedInstance;

QSharedPointer<Client> Client::Instance()
{
	if (sharedInstance.isNull()) {
		sharedInstance = QSharedPointer<Client>(new Client(NULL));
	}
	return sharedInstance;
}

Client::Client(QObject *parent) : QObject(parent)
{

}

bool Client::connectToServer(QHostAddress &addr, quint16 port)
{
	QString addrString = addr.toString();
	connection = QSharedPointer<TextShredderConnection>(new TextShredderConnection(this, addrString, port, false));

	connect(connection.data(), SIGNAL(clientDisconnected()),
			this, SLOT(connectionDidEncounterEnd()));
	connect(connection.data(), SIGNAL(statusChanged(TextShredderConnectionStatus, QAbstractSocket::SocketError)),
			this, SLOT(connectionStatusChanged(TextShredderConnectionStatus, QAbstractSocket::SocketError)));
	connect(connection.data(), SIGNAL(incomingSyncableFilesPacket(QByteArray&)),
			FileManager::Instance(), SLOT(handleReceivedSyncableFiles(QByteArray &)));
	connection.data()->startConnection();
	return true;
}

void Client::connectionStatusChanged(TextShredderConnectionStatus status, QAbstractSocket::SocketError error )
{
	if (status == Connected) {
		emit clientConnected();

		QString name("My name");
		SetAliasPacket packet(this, name);
		//connection.data()->write(packet);

	} else if (status == Error) {
		emit clientConnectionError(error);
	}
}

void Client::connectionDidEncounterEnd()
{

}

QSharedPointer<TextShredderConnection> Client::getConnection()
{
	return this->connection;
}
