#ifndef CLIENTREPRESENTATION_H
#define CLIENTREPRESENTATION_H

#include <QObject>
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




signals:

public slots:
	void getDisconnected();
	void getNameChanged(QString & changedName);

};

#endif // CLIENTREPRESENTATION_H
