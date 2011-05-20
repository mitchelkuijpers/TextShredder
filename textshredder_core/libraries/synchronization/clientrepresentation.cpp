#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = new TextShredderConnection(this, socketDescriptor);
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));

//	connect(connection, SIGNAL(incomingFileRequestPacketContent(QByteArray&)));

	connect(connection, SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			this, SLOT(processSetAliasPacketContent(QByteArray &)));

	connect(FileManager::Instance(), SIGNAL(updateClientFiles(TextShredderPacket&)),
			connection, SLOT(write(TextShredderPacket&)));
}

void ClientRepresentation::processSetAliasPacketContent(QByteArray &bytes)
{
	alias = QString(bytes);
}

void ClientRepresentation::getDisconnected()
{
	disconnect(connection, SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));
	disconnect(connection, SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			   this, SLOT(processSetAliasPacketContent(QByteArray &)));
	connection->deleteLater();
	emit clientRepresentationEncounteredEnd();
}

