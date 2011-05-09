#include "server.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "../libraries/synchronization/clientrepresentation.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	new ClientRepresentation(this, socketDescriptor);
}
