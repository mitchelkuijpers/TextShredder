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

	QList<SyncableFile *> syncableFiles;
	QString alias;

	void setClientName();

	QString * alias;


signals:

public slots:
	void getDisconnected(QString alias);

};

#endif // CLIENTREPRESENTATION_H
