#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = new TextShredderConnection(this, socketDescriptor);
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));


	connect(connection, SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			this, SLOT(processSetAliasPacketContent(QByteArray &)));
}

void ClientRepresentation::processSetAliasPacketContent(QByteArray &bytes)
{
	alias = QString(bytes);
}

void ClientRepresentation::getDisconnected()
{
}

void ClientRepresentation::getNameChanged(QString & changedName)
{
}
