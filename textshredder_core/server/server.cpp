#include "server.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../libraries/synchronization/clientrepresentation.h"

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
	ClientRepresentation *rep = new ClientRepresentation(this, socketDescriptor);
	clients.append(rep);
}

int Server::numberOfClients()
{
	return clients.count();
}

