#include "server.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../textshredder_synchronization_lib/workingcopy.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	SyncThread *thread = new SyncThread(this, socketDescriptor,
										*copy, true);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	QTcpSocket * tcp_sock_temp = new QTcpSocket();
	tcp_sock_temp->setSocketDescriptor(socketDescriptor);

	SyncableFile * syncfile = FileManager::Instance()->getFirstSyncableFileFromFileList();
	QString ipAddr = tcp_sock_temp->peerAddress().toString();
	syncfile->addClientWithName( ipAddr  );


	thread->start();
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
