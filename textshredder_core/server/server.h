#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QString>
#include "../libraries/synchronization/clientrepresentation.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
	static Server * Instance();

protected:
	void incomingConnection(int socketDescriptor);
private:
	Server(QObject *parent);

	bool listenWithFile(const QHostAddress &address, quint16 port);
	int numberOfClients();

	QList <ClientRepresentation *> clients;
	static Server * sharedInstance;
};

#endif // SERVER_H
