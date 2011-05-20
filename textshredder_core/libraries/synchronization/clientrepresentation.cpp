#include "clientrepresentation.h"

ClientRepresentation::ClientRepresentation(QObject *parent, int socketDescriptor) :
	QObject(parent)
{
	this->connection = QSharedPointer<TextShredderConnection> (
				new TextShredderConnection(this, socketDescriptor));
	connect(connection.data(), SIGNAL(clientDisconnected()), this, SLOT(getDisconnected()));

	connect(connection.data(), SIGNAL(incomingFileRequestPacket(TextShredderPacket&, quint16)),
							   this, SLOT(handleFileRequest(TextShredderPacket&,quint16)));

	connect(connection.data(), SIGNAL(incomingSetAliasPacketContent(QByteArray&)),
			this, SLOT(processSetAliasPacketContent(QByteArray &)));

	connect(FileManager::Instance(), SIGNAL(updateClientFiles(TextShredderPacket&)),
			connection.data(), SLOT(write(TextShredderPacket&)));
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
	connection.data()->deleteLater();
	emit clientRepresentationEncounteredEnd();
}

void ClientRepresentation::handleFileRequest(TextShredderPacket &packet,
													 quint16 destination)
{
	qDebug("ClientRepresentation::handleFileRequest");
	QString requestedFileIdentifier = FileRequestPacket::getFileIdentifier(packet);

	try {
		QSharedPointer<SyncableFile> file = FileManager::Instance()->getSyncableFileWithIdentifier(requestedFileIdentifier);
		qDebug() << "TODO: Handle file request MOFO!";
		file.data()->startSyncOn(destination, this->connection);
	} catch (QString exception) {
		qDebug() << exception;
		//Some error occured. Problably no such file.
	}
}



