#include "connectionlistener.h"

void ConnectionListener::incomingConnection(int socketDescriptor)
{
	emit newConnection(socketDescriptor);
}
