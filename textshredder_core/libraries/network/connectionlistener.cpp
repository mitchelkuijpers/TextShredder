#include "connectionlistener.h"

ConnectionListener::ConnectionListener(QObject * parent) :
		QTcpServer(parent)
{

}

void ConnectionListener::incomingConnection(int socketDescriptor)
{
	emit newConnection(socketDescriptor);
}
