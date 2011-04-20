#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QString>
#include "../textshredder_synchronization_lib/workingcopy.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
	bool listenWithFile(const QHostAddress &address, quint16 port, QByteArray * fileContent);

protected:
    void incomingConnection(int socketDescriptor);

private:
	WorkingCopy * copy;

};

#endif // SERVER_H
