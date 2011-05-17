#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include "models/syncablefile.h"
#include "../network/models/textshredderpacket.h"

class FileManager : public QObject
{
    Q_OBJECT

public:
	/**
	  * Singleton instance getter.
	  *
	  * @return the instance.
	  */
	static FileManager * Instance();

	/**
	  * Adds a file with a path to the SyncableFile list.
	  *
	  * @param the path to the file.
	  */
	void addFileWithPath(QString &path);

	/**
	  * Removes a file from the Syncable file list.
	  *
	  * @param the file to be removed.
	  */
	void removeFile(SyncableFile *file);

//	/**
//	  * Returns the first Syncable File from the SyncableFile list.
//	  *
//	  * @return the syncable file.
//	  */
//	SyncableFile & getFirstSyncableFileFromFileList();

	/**
	  * Adds a SyncableFile to the SyncableFile list.
	  *
	  * @return the syncable file.
	  */
	void addSyncFile(SyncableFile *file);

//	/**
//	  * Fills a List object with all alias names of the
//	  * SyncableFiles contained in the SyncableFile list.
//	  *
//	  * @param the list that should be filled.
//	  */
//	void fillListWithAllFileNames(QList<QString> &fileNames);

	/**
	  * Returns a SyncableFile with a given name from the SyncableFile
	  * list.
	  *
	  * @param the name of the SyncableFile needed.
	  *
	  * @return the syncable file.
	  */
	SyncableFile * getSyncableFileWithName(QString &name);


private:

	void fillListWithSharedFiles(QList <SyncableFile *> &list);
	FileManager(QObject *parent = 0);
	QList<SyncableFile *> fileList;
	static FileManager* sharedInstance;


private slots:
	void syncableFileStartedSharing();
	void syncableFileStoppedSharing();
	void shouldMakeRequestForSync(TextShredderPacket &packet);

signals:
	void fileStarted(SyncableFile *);
	void updateClientFiles(TextShredderPacket &);
	void sendFileRequest(TextShredderPacket &);
};

#endif // FILEMANAGER_H
