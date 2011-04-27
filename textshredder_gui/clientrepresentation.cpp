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

	SyncableFile * syncfile = FileManager::Instance()->getFirstSyncableFileFromFileList();
	QString ipAdress = connection->getPeerAdress();
	syncfile->addClientWithName(ipAdress);

	connect(sync, SIGNAL(sendDownload(TextShredderPacket &)),
			connection, SLOT(write(TextShredderPacket &)));

	setClientName();
}

void ClientRepresentation::setClientName()
{
	// only gets first fileb
	syncableFiles.append(FileManager::Instance()->getFirstSyncableFileFromFileList());
	alias->append(connection->getPeerAdress());

	if(syncableFiles.last()->addClientWithName(*alias)){

	}

}


void ClientRepresentation::getDisconnected()
{
	int i;
	for(i=0; i < syncableFiles.size(); i++ ){
		if(this->alias == syncableFiles.at(i)->getFileAlias()){
			if(syncableFiles.at(i)->removeClientWithName(*alias)){

			}
			break;
		}
	}
}

void ClientRepresentation::getNameChanged(QString & changedName)
{

	int i;
	for(i=0; i< syncableFiles.size(); i++){
		if(this->alias == syncableFiles.at(i)->getFileAlias()){
			if(syncableFiles.at(i)->changeClientName(*alias, changedName)){

			}
			break;
		}
	}
}
