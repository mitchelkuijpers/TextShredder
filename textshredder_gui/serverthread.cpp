#include "serverthread.h"

ServerThread::ServerThread(int socketDescriptor, QObject *parent):
    socketDescriptor(socketDescriptor), QThread(parent)
{
}

void ServerThread::run() {
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }
    while(1) {
        if(tcpSocket.waitForReadyRead(3000)){
            QByteArray data = tcpSocket.read(9999);
            tcpSocket.write(data);
        } else {
            tcpSocket.disconnectFromHost();
            break;
        }
    }

}
