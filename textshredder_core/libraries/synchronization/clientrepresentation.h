#ifndef CLIENTREPRESENTATION_H
#define CLIENTREPRESENTATION_H

#include <QObject>
#include <QString>
#include "../textshredder_synchronization_lib/textshredderconnection.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "filesync.h"

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
	FileSync * sync;
	QString alias;
	QList<SyncableFile *> syncableFiles;
	SyncThread *syncThread;
	SyncableFile *syncFile;
	void addClientNameToClientsList();

public slots:
	/**
	 * Removes the disconnected clients from the list
	 */
	void getDisconnected();

	/**
	 * Changes the name to changedName param
	 * @param QString changedName
	 */
	void getNameChanged(QString & changedName);

	/**
	 * Initiates a new syncthread and gets the working copy
	 */
	void fileSyncReady();

	/**
	 * ?? NOT CLEAR
	 * @param QByteArray bytes
	 */
	void processSetAliasPacketContent(QByteArray &bytes);

};

#endif // CLIENTREPRESENTATION_H
