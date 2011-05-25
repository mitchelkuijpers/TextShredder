#ifndef CLIENT_H
#define CLIENT_H

#include <QHostAddress>
#include "../libraries/network/textshredderconnection.h"

class Client : public QObject
{
    Q_OBJECT
public:

	static QSharedPointer<Client> Instance();
	bool connectToServer(QHostAddress &addr, quint16 port);
	QSharedPointer<TextShredderConnection> getConnection();

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
	void connectionDidEncounterEnd();
	void connectionSuccessful();
	void connectionError( QAbstractSocket::SocketError error );
	void connectionReceivedOnlineUsersPacket(TextShredderPacket &packet);
};

#endif // CLIENT_H
