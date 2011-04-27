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

	setClientName();
}

void ClientRepresentation::setClientName()
{
	syncableFiles.append( FileManager::Instance()->getFirstSyncableFileFromFileList());
	alias = connection->getPeerAdress();
	if(!syncableFiles.last()->addClientWithName(alias)){
		//FileManager::Instance()->;
	}



}


void ClientRepresentation::getDisconnected()
{
	int x;
	for(x=0; x < syncableFiles.size(); x++ ){
		if(QString::compare(syncableFiles.at(x)->getFileAlias(), this->alias)){
			//syncableFiles.at(x)->removeClientName();
			break;
		}
	}
}
