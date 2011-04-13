#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "serverthread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
