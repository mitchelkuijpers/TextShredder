#include "serverthread.h"

ServerThread::ServerThread(QObject *parent, int socketDescriptor, QByteArray * fileContent):
	QThread(parent), socketDescriptor(socketDescriptor), fileContent(fileContent)
{
}

void ServerThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
	}

	tcpSocket.write(*fileContent);
	tcpSocket.waitForBytesWritten(10000);
}


