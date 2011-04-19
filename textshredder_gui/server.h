#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "serverthread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
	bool listenWithFile(const QHostAddress &address, quint16 port, QByteArray * fileContent);

protected:
    void incomingConnection(int socketDescriptor);
private:
	QByteArray * fileContent;

};

#endif // SERVER_H
