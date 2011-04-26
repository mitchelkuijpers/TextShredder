#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <syncablefile.h>
class FileManager : public QObject
{
    Q_OBJECT

public:
	static FileManager * Instance();

	void addFileWithPath(QString &path);
	void removeFile(SyncableFile *file);
	SyncableFile * getFirstSyncableFileFromFileList();

private:
	FileManager(QObject *parent = 0);
	QList<SyncableFile *> fileList;
	static FileManager* sharedInstance;
};

#endif // FILEMANAGER_H
