#ifndef CLIENTREPRESENTATION_H
#define CLIENTREPRESENTATION_H

#include <QObject>
#include <QString>

#include "../network/textshredderconnection.h"
#include "syncthread.h"

class ClientRepresentation : public QObject
{
    Q_OBJECT
public:
	/**
	 * Constructor. Opens up a new connection on the socket descriptor.
	 * Gets the file to be synced and actually sync it.
	 * Add the client name to the client list
	 *
	 * @param parent The Parent object parent.
	 * @param socketDescriptor The socketdescriptor on which the connection is opened.
	 */
	ClientRepresentation(QObject *parent, int socketDescriptor);

	/**
	  * Method will return the current alias set by the client which the connection is connected to.
	  *
	  * @return The current alias.
	  */
	QString getAlias();

	/**
	  * Method will send an packet on the connection.
	  *
	  * @param packet The packet that should be send.
	  */
	void sendPacket(TextShredderPacket &packet);

	~ClientRepresentation();
private:
	/**
	  * Method will setup all the signals needed.
	  */
	void setupSignals();

	/**
	  * The connection on which this ClientRepresentation instance communicates.
	  */
	QSharedPointer<TextShredderConnection> connection;

	/**
	  * THe current set alias by the connected client.
	  */
	QString alias;

private slots:
	/**
	 * Will disconnect the signals from the connection, remove the alias from the user manager,
	 * and emit the signal clientRepresentationEncounteredEnd()
	 */
	void getDisconnected();

	/**
	  * Will handle a request from a file. This slot is connected to receivedFileRequest from the TextShredderConnextion.
	  *
	  * @param packet The packet containing the file request.
	  */
	void handleFileRequest(TextShredderPacket& packet);

	/**
	 * Will update the alias in the UserManager based on the bytes received in the SetAliasPacket.
	 *
	 * @param QByteArray bytes The content of the SetAliasPacket.
	 */
	void processSetAliasPacketContent(QByteArray &bytes);

signals:
	/**
	  * Signal that will be emitted when the connection ended.
	  */
	void clientRepresentationEncounteredEnd();

	/**
	  * Signal that will be emitted when the alias of the representation did change.
	  */
	void clientRepresentationDidChangeAlias();
};

#endif // CLIENTREPRESENTATION_H
