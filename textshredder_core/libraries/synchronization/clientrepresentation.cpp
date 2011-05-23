#include "clientrepresentation.h"
#include "../network/models/syncablefilespacket.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = QSharedPointer<TextShredderConnection> (
				new TextShredderConnection(this, socketDescriptor));
	connect(connection.data(), SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));

	connect(connection.data(), SIGNAL(incomingFileRequestPacket(TextShredderPacket&)),
							   this, SLOT(handleFileRequest(TextShredderPacket&)));

	connect(connection.data(), SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			this, SLOT(processSetAliasPacketContent(QByteArray &)));

	connect(FileManager::Instance(), SIGNAL(updateClientFiles(TextShredderPacket&)),
			connection.data(), SLOT(write(TextShredderPacket&)));

	//vraag huidige files op;
	// stuur een packet met de files;

	QSharedPointer<SyncableFilesPacket> packet((const QSharedPointer<SyncableFilesPacket>)FileManager::Instance()->getAvailableFilesPacket());
	connection.data()->write(*packet.data());
}

void ClientRepresentation::processSetAliasPacketContent(QByteArray &bytes)
{
	alias = QString(bytes);
}

void ClientRepresentation::getDisconnected()
{
	disconnect(connection.data(), SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));
	disconnect(connection.data(), SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			   this, SLOT(processSetAliasPacketContent(QByteArray &)));
	emit clientRepresentationEncounteredEnd();
	this->deleteLater();
}

void ClientRepresentation::handleFileRequest(TextShredderPacket &packet)
{
	qDebug("ClientRepresentation::handleFileRequest");
	QString requestedFileIdentifier = FileRequestPacket::getFileIdentifier(packet);

	try {
		QSharedPointer<SyncableFile> file = FileManager::Instance()->getSyncableFileWithIdentifier(requestedFileIdentifier);
		qDebug() << "TODO: Handle file request MOFO!";
		file.data()->startSyncOn(FileRequestPacket::getSourceHandle(packet), this->connection);
	} catch (QString exception) {
		qDebug() << exception;
		//Some error occured. Problably no such file.
	}
}



