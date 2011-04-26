#include "server.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "../textshredder_synchronization_lib/textshredderconnection.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	TextShredderConnection connection(this, socketDescriptor);
	SyncableFile * syncfile = FileManager::Instance()->getFirstSyncableFileFromFileList();
	QString ipAdress = connection.getPeerAdress();
	syncfile->addClientWithName(ipAdress);
}

bool Server::listenWithFile(const QHostAddress &address, quint16 port, QByteArray * fileContent)
{
	copy = new WorkingCopy(this);

	QString tempString;
	tempString.append(fileContent->data());
	copy->setContent(tempString);

	listen(address, port);
	return true;
}
