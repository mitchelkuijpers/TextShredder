#ifndef CLIENTREPRESENTATION_H
#define CLIENTREPRESENTATION_H

#include <QObject>
#include <QString>
#include "../textshredder_synchronization_lib/textshredderconnection.h"
#include "filesync.h"

class ClientRepresentation : public QObject
{
    Q_OBJECT
public:
	explicit ClientRepresentation(QObject *parent, int socketDescriptor);

private:
	TextShredderConnection * connection;
	FileSync * sync;
	QString alias;
	QList<SyncableFile *> syncableFiles;

	void addClientNameToClientsList();

public slots:
	void getDisconnected();
	void getNameChanged(QString & changedName);
	void fileSyncReady();
	void processSetAliasPacketContent(QByteArray &bytes);

};

#endif // CLIENTREPRESENTATION_H
