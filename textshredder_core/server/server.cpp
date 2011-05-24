#include "server.h"
#include "../libraries/synchronization/syncthread.h"
#include "../libraries/synchronization/clientrepresentation.h"
#include "../libraries/network/models/onlineuserspacket.h"
#include "usermanager.h"

Server * Server::sharedInstance = NULL;

Server * Server::Instance() {
	if (sharedInstance == NULL) {
		sharedInstance = new Server(NULL);
	}
	return sharedInstance;
}

Server::Server(QObject *parent):
    QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	QSharedPointer<ClientRepresentation> rep = QSharedPointer<ClientRepresentation>(
			new ClientRepresentation(this, socketDescriptor));
	connect(rep.data(), SIGNAL(clientRepresentationDidChangeAlias()), this, SLOT(processAliasChangeFromClientRepresentation()));
	connect(rep.data(), SIGNAL(clientRepresentationEncounteredEnd()), this, SLOT(removeClientRepresentationSlot()));
	clients.append(rep);
}

int Server::numberOfClients()
{
	return clients.count();
}

void Server::processAliasChangeFromClientRepresentation()
{
	sendUsersToAllClients();
}

void Server::sendUsersToAllClients()
{
	OnlineUsersPacket packet(this, UserManager::Instance()->getUsers());
	for (int i = 0; i < clients.count(); i++ ) {
		if (clients.at(i).isNull()) {
			qDebug() << "Object is null";
		} else {
			clients.at(i)->sendPacket(packet);
		}
	}
}

void Server::setServerAlias(QString newAlias)
{
	UserManager::Instance()->removeAlias(serverAlias);
	serverAlias = newAlias;
	serverAlias.append("(Server)");
	UserManager::Instance()->addAlias(serverAlias);
}

void Server::removeClientRepresentationSlot()
{
	qDebug() << "Server::removeClientRepresentationSlot";
	ClientRepresentation *rep = (ClientRepresentation *) sender();

	for (int i = 0; i < clients.count(); i ++ ) {
		QSharedPointer <ClientRepresentation> internalRep = clients.at(i);
		if (internalRep.isNull()) {
			clients.removeAt(i);
			i--;
		}
		else if (rep == internalRep.data()) {
			qDebug() << "Server::removeClientRepresentationSlot() error when uncommentign following line";
			//When uncommenting the following line there will be a crash.
			//The TextShredderConnectionWill be deallocated even when not uncommenting this line...
			//clients.removeAt(i);
			internalRep.clear();
			sendUsersToAllClients();
			return;
		}
	}
}

