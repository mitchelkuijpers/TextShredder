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

	QTcpSocket *tcp_sock_tmp = new QTcpSocket();
	tcp_sock_tmp->setSocketDescriptor(socketDescriptor);

	newIncomingConnection(tcp_sock_tmp->peerAddress().toString());
	qDebug() << tcp_sock_tmp->peerAddress().toString();
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
