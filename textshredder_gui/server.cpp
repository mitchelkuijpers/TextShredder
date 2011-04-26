#include "server.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "clientrepresentation.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	ClientRepresentation client(this, socketDescriptor);
}

bool Server::listenWithFile(const QHostAddress &address, quint16 port, QByteArray * fileContent)
{
	qDebug("start server");
	copy = new WorkingCopy(this);

	QString tempString;
	tempString.append(fileContent->data());
	copy->setContent(tempString);

	listen(address, port);
	return true;
}
