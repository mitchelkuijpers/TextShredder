#include "filesync.h"

FileSync::FileSync(QObject *parent, TextShredderConnection * connection) :
	QObject(parent), connection(connection)
{
	connect(this, SIGNAL(sendDownload(TextShredderPacket &)),
			connection, SLOT(write(TextShredderPacket &)));
	connect(connection, SIGNAL(incomingFileRequestPacketContent(QByteArray&)),
			this, SLOT(processFileRequest(QByteArray &)));
}

void FileSync::processFileRequest(QByteArray &)
{
	//TODO: Implement which file is requested
	createDownload();
}

void FileSync::createDownload() {
	FileManager * manager = FileManager::Instance();
	SyncableFile * file = manager->getFirstSyncableFileFromFileList();
	WorkingCopy * workingCopy = file->getWorkingCopy();
	QString * content = workingCopy->getContent();
	QByteArray packetContent;
	packetContent.append(*content);
	TextShredderPacket packet (this, kPacketTypeFileData, packetContent);
	emit sendDownload(packet);
	emit fileSyncFinished();
}


