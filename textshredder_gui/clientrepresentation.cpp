#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = new TextShredderConnection(this, socketDescriptor);
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));

	this->sync = new FileSync(this, this->connection);

	addClientNameToClientsList();
}

void ClientRepresentation::addClientNameToClientsList()
{
	qDebug("ClientRepresentation::addClientNameToClientsList()");

	//TODO: Currently add name to first file, should be file which the client is connected to
	syncableFiles.append(FileManager::Instance()->getFirstSyncableFileFromFileList());
	alias.append(connection->getPeerAdress());
	syncableFiles.at(0)->addClientWithName(alias);
}


void ClientRepresentation::getDisconnected()
{
	qDebug("ClientRepresentation::getDisconnected()");
	int i;
	for(i=0; i < syncableFiles.size(); i++ ){
		syncableFiles.at(i)->removeClientWithName(alias);
	}
}

void ClientRepresentation::getNameChanged(QString & changedName)
{
	int i;
	for(i=0; i< syncableFiles.size(); i++){
		syncableFiles.at(i)->changeClientName(alias, changedName);
	}
}
