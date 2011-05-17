#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QString>
#include "../libraries/synchronization/clientrepresentation.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
	Server(QObject *parent);

	bool listenWithFile(const QHostAddress &address, quint16 port);
	int numberOfClients();

protected:
	void incomingConnection(int socketDescriptor);

private:
	QList <ClientRepresentation *> clients;
};

#endif // SERVER_H
