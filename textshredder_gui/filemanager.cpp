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
	SyncableFile * file = new SyncableFile(this, path);
	fileList.append(file);
	emit fileStarted(file);
}

SyncableFile * FileManager::getFirstSyncableFileFromFileList()
{
	return fileList.at(0);
}

void FileManager::removeFile (SyncableFile *file)
{
	for (int i = 0; i < fileList.count(); i++ ) {
		SyncableFile *fileFromList = fileList.at(i);
		if (fileFromList == file) {
			fileList.removeAt(i);
			delete file;
			return;
		}
	}
}

void FileManager::addSyncFile(SyncableFile *file)
{
	fileList.append(file);
	emit fileStarted(file);
}

void FileManager::fillListWithAllFileNames(QList<QString> &fileNames)
{
	SyncableFile *fileFromList;
	for(int i = 0; i < fileList.count(); i++ ) {
		fileFromList = fileList.at(i);
		fileNames.append(fileFromList->getFileAlias());
	}
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
	return NULL;
}
