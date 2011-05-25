#include "client.h"
#include "../libraries/synchronization/filemanager.h"
#include "../libraries/network/models/setaliaspacket.h"
#include "../libraries/network/models/onlineuserspacket.h"
#include "../server/usermanager.h"

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
	connect(connection.data(), SIGNAL(socketConnectedSuccessfully()),
			this, SLOT(connectionSuccessful()));
	connect(connection.data(), SIGNAL(socketErrorReceived(QAbstractSocket::SocketError)),
			this, SLOT(connectionError(QAbstractSocket::SocketError)));
	connect(connection.data(), SIGNAL(incomingSyncableFilesPacket(QByteArray&)),
			FileManager::Instance(), SLOT(handleReceivedSyncableFiles(QByteArray &)));
	connect(connection.data(), SIGNAL(incomingOnlineUsersPacket(TextShredderPacket&)),
			this, SLOT(connectionReceivedOnlineUsersPacket(TextShredderPacket &)));
	connection.data()->startConnection();
	return true;
}

void Client::connectionSuccessful()
{
	emit clientConnected();
	SetAliasPacket packet(this, clientAlias);
	connection.data()->write(packet);
}

void Client::connectionError(QAbstractSocket::SocketError error )
{
	emit clientConnectionError(error);
}

void Client::connectionDidEncounterEnd()
{
	QList<QString> users;
	users << clientAlias;
	UserManager::Instance()->clearAndAddList(users);
}

QSharedPointer<TextShredderConnection> Client::getConnection()
{
	return this->connection;
}

void Client::setAlias(QString newAlias)
{
	clientAlias = newAlias;
}

void Client::connectionReceivedOnlineUsersPacket(TextShredderPacket &packet)
{
	QList<QString> userNames = OnlineUsersPacket::userListFromPacket(packet);
	UserManager::Instance()->clearAndAddList(userNames);
}
