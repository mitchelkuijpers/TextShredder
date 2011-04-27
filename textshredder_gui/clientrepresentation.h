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
	QString * alias;

signals:

public slots:

};

#endif // CLIENTREPRESENTATION_H
