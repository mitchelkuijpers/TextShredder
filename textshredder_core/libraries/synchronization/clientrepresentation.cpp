#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = new TextShredderConnection(this, socketDescriptor);
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));

	connect(connection, SIGNAL(incomingFileRequestPacket(TextShredderPacket&, quint16)),
							   this, SLOT(handleFileRequest(TextShredderPacket&,quint16)));

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

void ClientRepresentation::handleFileRequest(TextShredderPacket &packet,
													 quint16 destination)
{
	QString requestedFileName = FileRequestPacket::getFileIdentifier(packet);

	try {
		QSharedPointer<SyncableFile> file = FileManager::Instance()->getSyncableFileWithName(requestedFileName);
		qDebug() << "TODO: Handle file request MOFO!";
		//file.data()->createSynchronizationWithPortAndAddress(port, name);
	} catch (QString exception) {
		//Some error occured. Problably no such file.
	}
}



