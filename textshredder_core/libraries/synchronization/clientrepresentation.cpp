#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = new TextShredderConnection(this, socketDescriptor);
	connect(connection, SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));
	syncFile = FileManager::Instance()->getFirstSyncableFileFromFileList();
	this->sync = new FileSync(this, this->connection);
	connect(sync, SIGNAL(fileSyncFinished()), this, SLOT(fileSyncReady()));
	addClientNameToClientsList();

	connect(connection, SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			this, SLOT(processSetAliasPacketContent(QByteArray &)));
}

void ClientRepresentation::processSetAliasPacketContent(QByteArray &bytes)
{
	QString oldAlias(alias);
	alias = QString(bytes);
	for (int i = 0; i < syncableFiles.count(); i++ ) {
		syncableFiles.at(i)->changeClientName (oldAlias, alias);
	}
}

void ClientRepresentation::addClientNameToClientsList()
{
	syncableFiles.append(FileManager::Instance()->getFirstSyncableFileFromFileList());
	alias.append(connection->getPeerAdress());
	syncableFiles.at(0)->addClientWithName(alias);
}

void ClientRepresentation::fileSyncReady()
{
	syncThread = new SyncThread(this, *connection, *(syncFile->getWorkingCopy()));
}

void ClientRepresentation::getDisconnected()
{
	for(int i=0; i < syncableFiles.size(); i++ ){
		syncableFiles.at(i)->removeClientWithName(alias);
	}
}

void ClientRepresentation::getNameChanged(QString & changedName)
{
	for(int i=0; i< syncableFiles.size(); i++){
		syncableFiles.at(i)->changeClientName(alias, changedName);
	}
}
