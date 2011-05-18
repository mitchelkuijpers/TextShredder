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
	void removeFile(QSharedPointer<SyncableFile> file);

	/**
	  * Adds a SyncableFile to the SyncableFile list.
	  *
	  * @return the syncable file.
	  */
	void addSyncFile( QSharedPointer<SyncableFile> );

	/**
	  * Returns a SyncableFile with a given name from the SyncableFile
	  * list.
	  *
	  * @param the name of the SyncableFile needed.
	  *
	  * @return the syncable file.
	  */
	QSharedPointer<SyncableFile> getSyncableFileWithName(QString &name);

	QList < QSharedPointer<SyncableFile> > getAllFiles();

signals:
	void fileStarted(SyncableFile *);
	void updateClientFiles(TextShredderPacket &);
	void sendFileRequest(TextShredderPacket &);
	void availableFilesChanged();

private:

	void fillListWithSharedFiles(QList < QSharedPointer<SyncableFile> > &list);
	FileManager(QObject *parent = 0);
	QList< QSharedPointer<SyncableFile> > fileList;
	static FileManager* sharedInstance;


private slots:
	void syncableFileStartedSharing();
	void syncableFileStoppedSharing();
	void shouldMakeRequestForSync(TextShredderPacket &packet);
public slots:
	void handleReceivedSyncableFiles(QByteArray &content);
};

#endif // FILEMANAGER_H
