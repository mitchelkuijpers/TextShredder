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
	} else if (type == kPacketTypeFileData) {
		processDownload(packet);
	} else {
		qDebug("warning: Got a packet with a unkown type.");
	}
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
}

void FileSync::processDownload(TextShredderPacket &packet)
{
	qDebug("warning: processDownload not yet implemented.");
}


