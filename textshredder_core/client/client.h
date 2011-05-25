#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include "../libraries/network/textshredderconnection.h"

class Client : public QObject
{
    Q_OBJECT
public:

	static QSharedPointer<Client> Instance();
	/**
	 * Connect a number of signals and slots which need to be send on connecting
	 * to the server.
	 * @param &addr Address to connect to
	 * @param port The port it listens on.
	 * @return true.
	 */
	bool connectToServer(QHostAddress &addr, quint16 port);

	/**
	 * Returns a QSharedPointer which holds the current connection
	 */
	QSharedPointer<TextShredderConnection> getConnection();

	/**
	 * Set the client alias
	 * @param newAlias The alias to set.
	 */
	void setAlias(QString newAlias);

private:
	QSharedPointer<TextShredderConnection> connection;
	Client(QObject *parent);
	static QSharedPointer<Client> sharedInstance;
	QString clientAlias;

signals:
	void clientConnected();
	void clientConnectionError(QAbstractSocket::SocketError);
	void availableFilesRequest();

private slots:
	/**
	 * Creates a QList with QStrings
	 * Put the aliasses in the list
	 * Clear and add the new ALiasList
	 */
	void connectionDidEncounterEnd();
	/**
	 * Handle the status change in the connection
	 * When the status param is connected, it emits a signal,
	 * sets the alias packet and writes the packet to the connection.
	 * When the status param is error, it emits the clientconnectionerror signal
	 * @param status The status of the connection.
	 * @param error The error message which will be shown to the client.
	 */
	void connectionStatusChanged(TextShredderConnectionStatus status, QAbstractSocket::SocketError error );
	/**
	 * Creates a Qlist with usernames from onlineuserspacket.
	 * Clears and adds the list to the userManager
	 * @param &packet The packet which holds the users
	 */
	void connectionReceivedOnlineUsersPacket(TextShredderPacket &packet);
};

#endif // CLIENT_H
