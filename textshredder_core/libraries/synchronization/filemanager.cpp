#include "filemanager.h"

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
	QSharedPointer<SyncableFile> obj =
			QSharedPointer<SyncableFile>(new SyncableFile(this, path), SyncableFile::doDeleteLater);

	connect(obj.data(), SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	connect(obj.data(), SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	connect(obj.data(), SIGNAL(fileRequestsForSync(TextShredderPacket&)),
			this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	fileList.append(obj);

	emit fileStarted(obj.data());
}

void FileManager::removeFile (QSharedPointer<SyncableFile> file)
{
	for (int i = 0; i < fileList.count(); i++ ) {
		QSharedPointer<SyncableFile> fileFromList = fileList.at(i);
		if (fileFromList.data() == file.data()) {
			disconnect(file.data(), SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
			disconnect(file.data(), SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
			disconnect(file.data(), SIGNAL(fileRequestsForSync(TextShredderPacket&)), this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
			file.data()->stopSync();
			fileList.removeAt(i);
			break;
		}
	}
}

void FileManager::fillListWithSharedFiles(QList < QSharedPointer<SyncableFile> > &list)
{
	for ( int i = 0; i < fileList.count(); i++ ) {
		QSharedPointer <SyncableFile> file = fileList.at(i);
		if (file.data()->isShared()) {
			list.append(file);
		}
	}
}

QSharedPointer<SyncableFilesPacket> FileManager::getAvailableFilesPacket()
{
	QList< QSharedPointer<SyncableFile> > sharedFiles;
	fillListWithSharedFiles(sharedFiles);
	QSharedPointer<SyncableFilesPacket> packet( new SyncableFilesPacket(this, sharedFiles));
	return packet;
}

void FileManager::syncableFileStartedSharing()
{
	QSharedPointer<SyncableFilesPacket> packet((const QSharedPointer<SyncableFilesPacket>)getAvailableFilesPacket());
	emit updateClientFiles(*packet.data());
}

void FileManager::syncableFileStoppedSharing()
{
	QSharedPointer<SyncableFilesPacket> packet((const QSharedPointer<SyncableFilesPacket>)getAvailableFilesPacket());
	emit updateClientFiles(*packet.data());
}

void FileManager::shouldMakeRequestForSync(TextShredderPacket &packet)
{
	emit sendFileRequest(packet);
}

void FileManager::addSyncFile( QSharedPointer<SyncableFile> file)
{
	fileList.append(file);
	connect(file.data(), SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	connect(file.data(), SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	connect(file.data(), SIGNAL(fileRequestsForSync(TextShredderPacket&)), this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	emit fileStarted( file.data() );
}

QSharedPointer<SyncableFile> FileManager::getSyncableFileWithName(QString &name)
{
	QSharedPointer<SyncableFile> fileFromList;
	for(int i = 0; i < fileList.count(); i++ ) {
		fileFromList = fileList.at(i);
		if (fileFromList.data()->getFileAlias() == name) {
			return fileFromList;
		}
	}
	qDebug() << "FileManager::getSyncableFileWithName " << "No Such file shared";
	return fileFromList;
}

QSharedPointer<SyncableFile> FileManager::getSyncableFileWithIdentifier(QString &identifier)
{
	QSharedPointer<SyncableFile> fileFromList;
	for(int i = 0; i < fileList.count(); i++ ) {
		fileFromList = fileList.at(i);
		if (fileFromList.data()->getFileIdentifier() == identifier) {
			return fileFromList;
		}
	}
	qDebug() << "FileManager::getSyncableFileWithIdentifier " << "No Such file shared";
	return fileFromList;
}

void FileManager::handleReceivedSyncableFiles(QByteArray &content)
{
	QList< QSharedPointer<SyncableFile> > list;
	SyncableFilesPacket::fillListWithContentsOfPacket(list, content);

	for (int i = 0; i < list.count(); i ++ ) {
		QSharedPointer<SyncableFile> file = list.at(i);

		bool found = false;
		for (int j = 0; j < fileList.count(); j++) {
			if (file.data()->getFileIdentifier() == fileList.at(j).data()->getFileIdentifier()) {
				found = true;
			}
		}
		if (found == false) {
			addSyncFile(file);
		}
	}

	int i = 0;
	while( i < fileList.count()) {
		QSharedPointer<SyncableFile> existingFile = fileList.at(i);

		bool found = false;
		for (int j = 0; j < list.count(); j++) {
			QSharedPointer<SyncableFile> file = list.at(j);
			if (existingFile.data()->getFileIdentifier() == file.data()->getFileIdentifier()) {
				found = true;
			}
		}
		if (found == false) {

			this->removeFile(existingFile);
		} else {
			i++;
		}
	}

	emit availableFilesChanged();
}

QList<QSharedPointer<SyncableFile> > FileManager::getAllFiles()
{
	return fileList;
}
