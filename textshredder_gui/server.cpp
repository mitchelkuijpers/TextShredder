#include "server.h"
#include "serverthread.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	ServerThread *thread = new ServerThread(this, socketDescriptor, fileContent);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

bool Server::listenWithFile(const QHostAddress &address, quint16 port, QByteArray * fileContent)
{
	this->fileContent = fileContent;
	listen(address, port);

	return true;
}
