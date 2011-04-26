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

void FileManager::removeFile (SyncableFile *file) {
	for (int i = 0; i < fileList.count(); i++ ) {
		SyncableFile *fileFromList = fileList.at(i);
		if (fileFromList == file) {
			fileList.removeAt(i);
			delete file;
			return;
		}
	}
}
