#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{

	this->connection = new TextShredderConnection(this, socketDescriptor);
	this->sync = new FileSync(this, this->connection);

	addClientNameToClientsList();
}

void ClientRepresentation::addClientNameToClientsList()
{
	// only gets first file
	syncableFiles.append(FileManager::Instance()->getFirstSyncableFileFromFileList());
	alias.append(connection->getPeerAdress());
	syncableFiles.at(0)->addClientWithName(alias);
}


void ClientRepresentation::getDisconnected()
{
	qDebug("getDisconnected");
	int i;
	for(i=0; i < syncableFiles.size(); i++ ){
		if(QString::compare(alias, syncableFiles.at(i)->getFileAlias()) == 0){
			syncableFiles.at(i)->removeClientWithName(alias);

			break;
		}
	}
}

void ClientRepresentation::getNameChanged(QString & changedName)
{
	int i;
	for(i=0; i< syncableFiles.size(); i++){
		if(QString::compare(alias, syncableFiles.at(i)->getFileAlias()) == 0){
			syncableFiles.at(i)->changeClientName(alias, changedName);
			break;
		}
	}
}
