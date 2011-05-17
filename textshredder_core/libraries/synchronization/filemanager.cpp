#include "filemanager.h"
#include "../network/models/syncablefilespacket.h"

FileManager* FileManager::sharedInstance = NULL;

FileManager::FileManager(QObject *parent) :
    QObject(parent)
{
}

FileManager * FileManager::Instance()
{
	if (!sharedInstance ) {
		sharedInstance = new FileManager(NULL);
	}
	return sharedInstance;
}

void FileManager::addFileWithPath(QString &path)
{
	qDebug("FileManager::addFileWithPath() - We are now sharing a file");
	SyncableFile *newFile = new SyncableFile(this, path);
	connect(newFile, SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	connect(newFile, SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	connect(newFile, SIGNAL(fileRequestsForSync(TextShredderPacket&)),
			this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	fileList.append(newFile);

	qDebug("TODO: fileManager file.setShared should be removed eventually");
	newFile->setShared(true);
	emit fileStarted(newFile);
}

void FileManager::removeFile (SyncableFile *file)
{
	for (int i = 0; i < fileList.count(); i++ ) {
		SyncableFile *fileFromList = fileList.at(i);
		if (fileFromList == file) {
			disconnect(fileFromList, SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
			disconnect(fileFromList, SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
			disconnect(fileFromList, SIGNAL(fileRequestsForSync(TextShredderPacket&)), this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
			fileFromList->stopSync();
			fileList.removeAt(i);

			fileFromList->deleteLater();
			return;
		}
	}
}

void FileManager::fillListWithSharedFiles(QList <SyncableFile *> &list)
{
	for ( int i = 0; i < fileList.count(); i++ ) {
		SyncableFile *file = fileList.at(i);
		if (file->isShared()) {
			list.append(file);
		}
	}
}

void FileManager::syncableFileStartedSharing()
{
	QList<SyncableFile *> sharedFiles;
	fillListWithSharedFiles(sharedFiles);
	SyncableFilesPacket packet(this, sharedFiles);
	emit updateClientFiles(packet);
}

void FileManager::syncableFileStoppedSharing()
{
	SyncableFilesPacket packet(this, fileList);
	emit updateClientFiles(packet);
}

void FileManager::shouldMakeRequestForSync(TextShredderPacket &packet)
{
	emit sendFileRequest(packet);
}

void FileManager::addSyncFile(SyncableFile *file)
{
	fileList.append(file);
	connect(file, SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	connect(file, SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	connect(file, SIGNAL(fileRequestsForSync(TextShredderPacket&)), this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	emit fileStarted(file);
}

SyncableFile * FileManager::getSyncableFileWithName(QString &name)
{
	SyncableFile *fileFromList;
	for(int i = 0; i < fileList.count(); i++ ) {
		fileFromList = fileList.at(i);
		if (fileFromList->getFileAlias() == name) {
			return fileFromList;
		}
	}
	throw QString("No Such file shared");
	return fileFromList;
}

void FileManager::handleReceivedSyncableFiles(QByteArray &content)
{
	QList<SyncableFile *> list;
	SyncableFilesPacket::fillListWithContentsOfPacket(list, content);

	for (int i = 0; i < list.count(); i ++ ) {
		SyncableFile *file = list.at(i);

		bool found = false;
		for (int j = 0; j < fileList.count(); j++) {
			if (file->getFileIdentifier() == fileList.at(j)->getFileIdentifier()) {
				found = true;
			}
		}
		if (found == false) {
			SyncableFile *newFile = new SyncableFile(*file);
			fileList.append(newFile);
		}
	}

	int i = 0;
	while( i < fileList.count()) {
		SyncableFile *existingFile = fileList.at(i);

		bool found = false;
		for (int j = 0; j < list.count(); j++) {
			SyncableFile *file = list.at(j);
			if (existingFile->getFileIdentifier() == file->getFileIdentifier()) {
				found = true;
			}
		}
		if (found == false) {
			fileList.removeAt(i);
		} else {
			i++;
		}
	}

	qDebug("Your momma. Trekt zich af op de meisjes wc");
	emit availableFilesChanged();
}
