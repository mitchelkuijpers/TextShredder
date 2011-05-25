#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include <QTcpServer>

class ConnectionListener : public QTcpServer
{
    Q_OBJECT
public:
	/**
	 * Constructor, passes the parent parameter to QTcpServer
	 * @param *parent To have access to the Q methods
	 */
	ConnectionListener(QObject * parent);

protected:
	/**
	 * Emits a newConnection to the socket
	 * @param socketDescriptor The socketdescriptor to to emit the new connection to
	 */
	void incomingConnection(int socketDescriptor);

signals:
	void newConnection(quint16);

};

#endif // CONNECTIONLISTENER_H
