#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
    QObject(parent)
{
	this->connection = new TextShredderConnection(this, socketDescriptor);
	this->sync = new FileSync(this, this->connection);

	connect(connection, SIGNAL(newIncomingPacket(TextShredderPacket &)),
			sync, SLOT(processNewPacket(TextShredderPacket &)));

	connect(sync, SIGNAL(sendDownload(TextShredderPacket &)),
			connection, SLOT(write(TextShredderPacket &)));

	connect(sync, SIGNAL(sendDownload(TextShredderPacket &)),
			connection, SLOT(write(TextShredderPacket &)));

	SyncableFile * syncfile = FileManager::Instance()->getFirstSyncableFileFromFileList();
	QString ipAdress = connection->getPeerAdress();
	syncfile->addClientWithName(ipAdress);
}
