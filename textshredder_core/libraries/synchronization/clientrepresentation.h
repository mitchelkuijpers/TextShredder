#ifndef CLIENTREPRESENTATION_H
#define CLIENTREPRESENTATION_H

#include <QObject>
#include <QString>
#include "../network/textshredderconnection.h"
#include "./syncthread.h"
#include "./filesync.h"

class ClientRepresentation : public QObject
{
    Q_OBJECT
public:
	/**
	 * Constructor. Opens up a new connection on the socket
	 * Gets the file to be synced and actually sync it.
	 * Add the client name to the client list
	 *
	 * @param Qobject parent.
	 * @param int The socketdescriptor
	 */
	explicit ClientRepresentation(QObject *parent, int socketDescriptor);

private:
	TextShredderConnection * connection;
	QString alias;

private slots:
	/**
	 * Removes the disconnected clients from the list
	 */
	void getDisconnected();
	void handleFileRequest(TextShredderPacket& packet, quint16 destination);

	/**
	 * ?? NOT CLEAR
	 * @param QByteArray bytes
	 */
	void processSetAliasPacketContent(QByteArray &bytes);

signals:
	void clientRepresentationEncounteredEnd();
};

#endif // CLIENTREPRESENTATION_H
