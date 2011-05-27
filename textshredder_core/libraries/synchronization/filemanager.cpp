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
			QSharedPointer<SyncableFile>(new SyncableFile(this, path));

	obj.data()->setOnServer(isServer);
	connectSignalsForSyncableFile(obj.data());

	fileList.append(obj);

	if(isServer){
		backupDir.mkdir("serverBackup");
		QTimer *backupTimer = new QTimer(this);
		backupTimer->start(30000);
		connect(backupTimer, SIGNAL(timeout()), this, SLOT(backupServerContent()));
	}

	emit fileStarted(obj.data());
}

void FileManager::removeFile (QSharedPointer<SyncableFile> file)
{
	for (int i = 0; i < fileList.count(); i++ ) {
		QSharedPointer<SyncableFile> fileFromList = fileList.at(i);
		if (fileFromList.data() == file.data()) {
			disconnectSignalsForSyncableFile(file.data());
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
	file.data()->setOnServer(isServer);
	connect(file.data(), SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	connect(file.data(), SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	connect(file.data(), SIGNAL(syncableFileChanged()), this, SLOT(syncableFileDidChange()));
	connect(file.data(), SIGNAL(fileRequestsForSync(TextShredderPacket&)), this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	emit fileStarted( file.data() );
}

void FileManager::syncableFileDidChange() {
	emit availableFilesChanged();
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
				fileList.at(j).data()->setShared(true);
				fileList.at(j).data()->setFileAlias(file.data()->getFileAlias());
				found = true;
			}
		}
		if (found == false) {
			file.data()->setShared(true);
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

void FileManager::setServerSide(bool value)
{
	isServer = value;
}
bool FileManager::isServerSide()
{
	return isServer;
}

void FileManager::backupSyncableFile( SyncableFile * file )
{
	QString path = "serverBackup/backup" + file->getFileAlias();
	QFile backupFile(path);
	qDebug() << "path: " << path;
	backupFile.open(QIODevice::WriteOnly | QIODevice::Text);
	backupFile.write(file->getWorkingCopy().data()->getContent()->toStdString().c_str());
}

void FileManager::backupServerContent()
{
	for(int i=0; i < this->getAllFiles().count(); i++){
		if(fileList.at(i).data()->calculateStatus() == Syncing){
			backupSyncableFile(fileList.at(i).data());
		}
	}
}


void FileManager::syncableFileShouldBeRemoved()
{
	SyncableFile *fileToRemove = (SyncableFile *)sender();
	for (int i = 0; i < this->fileList.count(); i ++) {
		QSharedPointer<SyncableFile> existing = fileList.at(i);
		if (existing.data() == fileToRemove) {
			fileList.removeAt(i);
			return;
		}
	}
}

void FileManager::connectSignalsForSyncableFile( SyncableFile *file )
{
	connect(file, SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	connect(file, SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	connect(file, SIGNAL(syncableFileChanged()), this, SLOT(syncableFileDidChange()));
	connect(file, SIGNAL(fileRequestsForSync(TextShredderPacket&)),
			this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	connect(file, SIGNAL(fileShouldBeBackedUp( SyncableFile * )),
			this, SLOT(backupSyncableFile(SyncableFile*)));
}

void FileManager::disconnectSignalsForSyncableFile( SyncableFile *file )
{
	disconnect(file, SIGNAL(fileStartedSharing()), this, SLOT(syncableFileStartedSharing()));
	disconnect(file, SIGNAL(fileStoppedSharing()), this, SLOT(syncableFileStoppedSharing()));
	disconnect(file, SIGNAL(syncableFileChanged()), this, SLOT(syncableFileDidChange()));
	disconnect(file, SIGNAL(fileRequestsForSync(TextShredderPacket&)),
			   this, SLOT(shouldMakeRequestForSync(TextShredderPacket &)));
	disconnect(file, SIGNAL(fileShouldBeBackedUp( SyncableFile * )),
			   this, SLOT(backupSyncableFile(SyncableFile*)));
}
