#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QDir>
#include "models/syncablefile.h"
#include "../network/models/textshredderpacket.h"
#include "../network/models/syncablefilespacket.h"
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
	  * @param name The name of the SyncableFile needed.
	  *
	  * @return The syncable file.
	  */
	QSharedPointer<SyncableFile> getSyncableFileWithName(QString &name);

	/**
	  * Returns a SyncableFile with a given identifier from the SyncableFile
	  * list.
	  *
	  * @param identifier The identifier of the SyncableFile needed.
	  *
	  * @return The syncable file.
	  */
	QSharedPointer<SyncableFile> getSyncableFileWithIdentifier(QString &identifier);

	/**
	  * Method will return all available syncable files.
	  *
	  * @return The list with SyncableFile objects.
	  */
	QList < QSharedPointer<SyncableFile> > getAllFiles();

	/**
	  * Method will return a packet containing the information about the available files
	  * that are currently shared.
	  *
	  * @return The SynableFilesPacket created.
	  */
	QSharedPointer<SyncableFilesPacket> getAvailableFilesPacket();

	/**
	  * Method will set a value to let the FileManager know if it is on the server side or not.
	  *
	  * @param value The value if it is on server. TRUE if so, FALSE if not.
	  */
	void setServerSide(bool value);

	/**
	  * Method will return a boolean value if the filemanager runs as server.
	  *
	  * @return True if on server false if not.
	  */
	bool isServerSide();

signals:
	/**
	  * Signal that will be emitted when a file is started.
	  */
	void fileStarted(SyncableFile *);

	/**
	  * Signal that will be emitted when filemanager is as 'server', the parameter that will be emitted
	  * is a packet representing the SyncableFile objects.
	  */
	void updateClientFiles(TextShredderPacket &);

	/**
	  * Signal that will be emitted when a file request should send.
	  *
	  * @param packet The packet that has to be send.
	  */
	void sendFileRequest(TextShredderPacket &packet);

	/**
	  * Signal that will be emitted when the files in the filemanager changes.
	  */
	void availableFilesChanged();

private:

	/**
	  * Method that will connect the neccasary signals to slots for a syncable file.
	  *
	  * @param file The SyncableFile that needs to be connected.
	  */
	void connectSignalsForSyncableFile( SyncableFile *file );

	/**
	  * Method that will disconnect	 the neccasary signals to slots for a syncable file.
	  *
	  * @param file The SyncableFile that needs to be disconnected.
	  */
	void disconnectSignalsForSyncableFile( SyncableFile *file );

	/**
	  * Method that will fill a list with all shared files.
	  *
	  * @param list The list that has to be filled.
	  */
	void fillListWithSharedFiles(QList < QSharedPointer<SyncableFile> > &list);

	/**
	  * Private contructor for the singleton.
	  */
	FileManager(QObject *parent = 0);

	/**
	  * The list with SyncableFile objects.
	  */
	QList< QSharedPointer<SyncableFile> > fileList;

	/**
	  * Pointer to the sharedInstance for the singleton.
	  */
	static FileManager* sharedInstance;

	/**
	  * Value if the filemanager is on the server.
	  */
	bool isServer;

	/**
	  * The directory for the backups.
	  */
	QDir backupDir;

public slots:

	/**
	  * Slot that is used when a file started sharing.
	  * Will emit the updateClientFiles() signal.
	  */
	void syncableFileStartedSharing();

	/**
	  * Slot that is used when a file started sharing.
	  * Will emit the updateClientFiles() signal.
	  */
	void syncableFileStoppedSharing();

	/**
	  * Slot that is used when a SyncableFile want to make a file request.
	  * Will emit the sendFileRequest() signal.
	  */
	void shouldMakeRequestForSync(TextShredderPacket &packet);

	/**
	  * Slot that is used when file did change.
	  * Will emit the availableFilesChanged() signal.
	  */
	void syncableFileDidChange();

	/**
	  * Slot that will be called by the timer to make a backup for a file.
	  * The backup will only be made for files that are currently being synced.
	  */
	void backupServerContent();

	/**
	  * Slot that will be called when file should be removed.
	  * Normally called when a file is closed and not shared on the client side.
	  */
	void syncableFileShouldBeRemoved();

	/**
	  * Slot will backup a SyncableFile.
	  */
	void backupSyncableFile( SyncableFile *file );

	/**
	  * Slot that will be called when SyncableFile data is received.
	  *
	  * @param content The content of the SyncableFilesPacket.
	  */
	void handleReceivedSyncableFiles(QByteArray &content);
};

#endif // FILEMANAGER_H
