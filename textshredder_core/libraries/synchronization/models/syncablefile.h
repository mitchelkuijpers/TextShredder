#ifndef SYNCABLEFILE_H
#define SYNCABLEFILE_H

#include <QObject>
#include "../textshredder_core/libraries/synchronization/models/workingcopy.h"
#include "../syncthread.h"
#include "../../network/models/filerequestpacket.h"

typedef enum {
	Unknown = 1,
	Unshared = 2,
	UnopenedSharedFile =3,
	Idle = 4,
	Editing = 5,
	Syncing = 6,
	Offline = 7
} SyncableFileStatus;

typedef enum {
	FileTypeUNKNOWN = 1,
	FileTypeTXT = 2,
	FileTypePHP = 3,
	FileTypeHTML = 4
} FileType;

class SyncableFile : public QObject
{
    Q_OBJECT
public:

	/**
	  * Constructor to create a SyncableFile with a parent and a path on which its content is loaded.
	  *
	  * @param parent The parent object.
	  * @param path The path on which the file content is loaded.
	  */
	SyncableFile( QObject *parent, QString &path );

	/**
	  * Constructor to create a SyncableFile with a parent, alias and type.
	  *
	  * @param parent The parent object.
	  * @param path The alias of the file.
	  * @param type The type of the file.
	  */
	SyncableFile( QObject *parent, QString &alias, FileType type );

	/**
	  * Constructor to create a SyncableFile with a parent, identifier and alias.
	  *
	  * @param parent The parent object.
	  * @param identifier The uniqueIdentifier of the file.
	  * @param alias The alias for the file.
	  */
	SyncableFile( QObject *parent, QString &identifier, QString & alias );

	/**
	  * Copy Constructor.
	  *
	  * @param other SyncableFile which is being copied.
	  */
	SyncableFile(const SyncableFile &other);

	/**
	  * Operator overload for the = operator.
	  * Will assign this object to the object passed as parameter.
	  *
	  * @param other SyncableFile which this object is being assigned to.
	  *
	  * @return The new assigned object (this).
	  */
	SyncableFile & operator=(const SyncableFile & other);

	/**
	  * Operator overload for the == operator.
	  * Will compare the object to the other object passed as parameter.
	  *
	  * @param other SyncableFile which this object is being compared to.
	  *
	  * @return The result. True if objects are equal.
	  */
	bool operator == (const SyncableFile & other);

	/**
	  * Will change the file type for the SyncableFile
	  */
	void changeFileType(FileType type);

	/**
	  * Method will start a SyncThread with an destination handle.
	  *
	  * @param destination The destination the SyncThread packets are send to.
	  * @param connection The connection on which the SyncThread will communicate.
	  */
	void startSyncOn( quint16 destination, QSharedPointer<TextShredderConnection> connection );

	/**
	  * Method will stop the SyncThreads in the SyncableFile object.
	  */
	void stopSync();

	/**
	  * Method will return a shared pointer to the workingCopy.
	  * @return The workingCopy;
	  */
	QSharedPointer<WorkingCopy> getWorkingCopy();

	/**
	  * Method will return the fileAlias.
	  *
	  * @return The fileAlias;
	  */
	QString & getFileAlias();

	/**
	  * Method will set the file alias to the newFileAlias parameter.
	  *
	  * @param newAlias The new alias stored in the SyncableFile object.
	  */
	void setFileAlias(QString &);

	/**
	  * Method will return the fileIdentifier.
	  *
	  * @return The fileIdentifier;
	  */
	QString & getFileIdentifier();

	/**
	  * Method checks if file isShared.
	  *
	  * @return Is true if file isShared.
	  */
	bool isShared();

	/**
	  * Method checks if file is on server.
	  *
	  * @return Is true if file is on server.
	  */
	bool isOnServer();

	/**
	  * Method checks if file is opened.
	  *
	  * @return Is true if file is opened.
	  */
	bool isOpened();

	/**
	  * Method sets the shared value to the given value.
	  * The signal for fileStartedSharing or fileStoppedSharing will be emitted when the value changes to true or false.
	  * If syncing ends on the server. The file is saved and all SyncThreads are stopped.
	  * Method will always emit the syncableFileChanged signal.
	  *
	  * @param the new value off isShared.
	  */
	void setShared(bool share);

	/**
	  * Method sets the onServer value to the given value.
	  *
	  * @param the new value off isShared.
	  */
	void setOnServer(bool value);

	/**
	  * Method will set the isOpened variable to false and will stop the SyncThread objects if on client.
	  * If the SyncableFile is not shared on the client. This funcion will also emit the syncableFileShouldBeRemoved signal.
	  * Method will always emit the syncableFileChanged signal.
	  */
	void close();

	/**
	  * Method will set the isOpened variable to true and emit the syncableFileChanged signal.
	  * Method will call requestSync() when its variable onServer is true.
	  */
	void open();

	/**
	  * Method will calculate the current status for the SyncableFile object.
	  *
	  * @return The current status for the file.
	  */
	SyncableFileStatus calculateStatus();

private:
	/**
	  * Method wil save a file.
	  */
	void saveFileToPath();

	/**
	  * Function will request a sync for this SyncableFile object.
	  */
	void requestSync();

	/**
	  * Method will return a file type for a given textual representation of a suffix.
	  */
	FileType typeForSuffix(QString &suffix);

	/**
	  * The unique identifier for the file.
	  */
	QString fileIdentifier;

	/**
	  * The file path the file is loaded from.
	  */
	QString filePath;

	/**
	  * The file alias for the file.
	  */
	QString fileAlias;

	/**
	  * The working copy for the file.
	  */
	QSharedPointer<WorkingCopy> workingCopy;

	/**
	  * The type of the file.
	  */
	FileType fileType;

	/**
	  * boolean value if the file is shared.
	  */
	bool shared;

	/**
	  * boolean value if the file is opened.
	  */
	bool opened;

	/**
	  * boolean value if the file is on the server.
	  */
	bool onServer;

	/**
	  * List of SyncThread object which the file is synchronized on.
	  */
	QList< QSharedPointer<SyncThread> > syncThreads;

private slots:
	/**
	  * Slot to process if syncThread stopped by other node.
	  * Method will call saveFileToPath() when there are no SyncThread objects left on the server.
	  */
	void syncThreadIsStoppedByOtherNode();

signals:
	/** Emitted when isShared is put to true */
	void fileStoppedSharing();

	/** Emitted when isShared is put to false */
	void fileStartedSharing();

	/** Emitted when a request packet is made and should be emitted */
	void fileRequestsForSync(TextShredderPacket &);

	/** Emitted when the file internally changes */
	void syncableFileChanged();

	/** Emitted when the file should be cleared out of memory */
	void syncableFileShouldBeRemoved();

	/** Emitted when syncing ends on server */
	void fileShouldBeBackedUp();
};

#endif // SYNCABLEFILE_H
