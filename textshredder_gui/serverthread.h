#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(int socketDescriptor, QObject *parent);
signals:
    void error(QTcpSocket::SocketError socketError);
private:
    int socketDescriptor;
    void run();
};

#endif // SERVERTHREAD_H
