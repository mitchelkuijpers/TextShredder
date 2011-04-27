#include "filesync.h"

FileSync::FileSync(QObject *parent, TextShredderConnection * connection) :
	QObject(parent), connection(connection)
{
	connect(this, SIGNAL(sendDownload(TextShredderPacket &)),
			connection, SLOT(write(TextShredderPacket &)));
	connect(connection, SIGNAL(newIncomingPacket(TextShredderPacket &)),
			this, SLOT(processNewPacket(TextShredderPacket &)));
}

void FileSync::processNewPacket(TextShredderPacket &packet)
{
	unsigned int type = packet.getHeader().getPacketType();
	if(type == kPacketTypeFileRequest) {
		createDownload();
	} else {
		qDebug("warning: Got a packet with a unhandable type.");
	}
}

void FileSync::createDownload() {
	qDebug("FileSync::createDownload()");
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


