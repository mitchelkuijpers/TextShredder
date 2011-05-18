#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include <QTcpServer>

class ConnectionListener : public QTcpServer
{
    Q_OBJECT
protected:
	void incomingConnection(int socketDescriptor);

signals:
	void newConnection(quint16);

};

#endif // CONNECTIONLISTENER_H
