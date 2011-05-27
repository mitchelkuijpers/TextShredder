#include "clientrepresentation.h"
#include "../network/models/syncablefilespacket.h"
#include "../../server/usermanager.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = QSharedPointer<TextShredderConnection> (
				new TextShredderConnection(this, socketDescriptor));


	QSharedPointer<SyncableFilesPacket> packet = FileManager::Instance()->getAvailableFilesPacket();
	sendPacket(*packet.data());

	setupSignals();
}

void ClientRepresentation::setupSignals()
{
	connect(connection.data(), SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));

	connect(connection.data(), SIGNAL(incomingFileRequestPacket(TextShredderPacket&)),
							   this, SLOT(handleFileRequest(TextShredderPacket&)));

	connect(connection.data(), SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			this, SLOT(processSetAliasPacketContent(QByteArray &)));

	connect(FileManager::Instance(), SIGNAL(updateClientFiles(TextShredderPacket&)),
			connection.data(), SLOT(write(TextShredderPacket&)));
}

void ClientRepresentation::processSetAliasPacketContent(QByteArray &bytes)
{
	UserManager::Instance()->removeAlias(alias);
	alias = QString(bytes);
	UserManager::Instance()->addAlias(alias);
	emit clientRepresentationDidChangeAlias();
}

void ClientRepresentation::getDisconnected()
{

	disconnect(connection.data(), SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));
	disconnect(connection.data(), SIGNAL(incomingFileRequestPacket(TextShredderPacket&)), this, SLOT(handleFileRequest(TextShredderPacket&)));
	disconnect(connection.data(), SIGNAL(incomingSetAliasPacketContent(QByteArray&)), this, SLOT(processSetAliasPacketContent(QByteArray &)));
	disconnect(FileManager::Instance(), SIGNAL(updateClientFiles(TextShredderPacket&)), connection.data(), SLOT(write(TextShredderPacket&)));

	UserManager::Instance()->removeAlias(alias);
	emit clientRepresentationEncounteredEnd();
}

void ClientRepresentation::handleFileRequest(TextShredderPacket &packet)
{
	QString requestedFileIdentifier = FileRequestPacket::getFileIdentifier(packet);

	try {
		QSharedPointer<SyncableFile> file = FileManager::Instance()->getSyncableFileWithIdentifier(requestedFileIdentifier);
		file.data()->startSyncOn(FileRequestPacket::getSourceHandle(packet), this->connection);
	} catch (QString exception) {
		qDebug() << exception;
		//Some error occured. Problably no such file.
	}
}

QString ClientRepresentation::getAlias()
{
	return alias;
}

void ClientRepresentation::sendPacket(TextShredderPacket &packet)
{
	connection.data()->write(packet);
}



