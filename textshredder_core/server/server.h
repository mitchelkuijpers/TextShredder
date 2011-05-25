#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QString>
#include "../libraries/synchronization/clientrepresentation.h"

class Server : public QTcpServer
{
	Q_OBJECT
public:
	/**
	 * Returns a singleton instance of the Server
	 */
	static Server * Instance();
	/**
	 * Set the server alias and emit its change
	 * @param newAlias The alias to set.
	 */
	void setServerAlias(QString newAlias);
	/**
	 * Gets the Clients from the OnlineUsersPacket and send the userspacket to them
	 */
	void sendUsersToAllClients();

protected:
	/**
	 * Connects signals to the incomingconnection.
	 * @param socketDescriptor The socketdescriptor of the incomingconnection
	 */
	void incomingConnection(int socketDescriptor);
private:

	Server(QObject *parent);

	/**
	 *	Returns the number of clients
	 */
	int numberOfClients();

	QString serverAlias;

	QList < QSharedPointer<ClientRepresentation> > clients;
	static Server * sharedInstance;

private slots:
	void processAliasChangeFromClientRepresentation();
	void removeClientRepresentationSlot();
};

#endif // SERVER_H
