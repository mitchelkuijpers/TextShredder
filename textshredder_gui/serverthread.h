#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class ServerThread : public QThread
{
    Q_OBJECT
public:
	ServerThread(QObject *parent, int socketDescriptor, QByteArray * fileContent);
signals:
    void error(QTcpSocket::SocketError socketError);
private:
    int socketDescriptor;
	void run();
	QByteArray * fileContent;
};

#endif // SERVERTHREAD_H
