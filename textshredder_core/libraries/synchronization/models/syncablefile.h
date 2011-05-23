#ifndef SYNCABLEFILE_H
#define SYNCABLEFILE_H

#include <QObject>
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "../syncthread.h"
#include "../../network/models/filerequestpacket.h"

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
	SyncableFile(QObject *parent, QString &path);
	SyncableFile(QObject *parent, QString &alias, FileType type);
	SyncableFile(const SyncableFile &other);
	SyncableFile(QObject *parent, QString &identifier, QString &alias);

	SyncableFile & operator=(const SyncableFile & other);
	bool operator == (const SyncableFile & other);
	/**
	  * Will change the file type for the SyncableFile
	  */
	void changeFileType(FileType type);
	void startSyncOn(quint16, QSharedPointer<TextShredderConnection> connection);
	void stopSync();
	QSharedPointer<WorkingCopy> getWorkingCopy();
	QString & getFileAlias();
	void setFileAlias(QString &);
	QString & getFileIdentifier();

	bool isShared();
	bool isOnServer();
	bool isOpened();

	void setShared(bool share);
	void setOnServer(bool value);

	void close();
	void open();

	void requestSync();

	static void doDeleteLater(SyncableFile *obj);

	QSharedPointer<WorkingCopy> openWorkingCopyForGUI();
	void closeWorkingCopyFromGUI();

private:
	QString fileIdentifier;
	FileType typeForSuffix(QString &suffix);
	QString filePath;
	QString fileAlias;
	QSharedPointer<WorkingCopy> workingCopy;
	FileType fileType;
	bool shared;
	bool opened;
	bool onServer;

	QList< QSharedPointer<SyncThread> > syncThreads;

private slots:
	void syncThreadIsStoppedByOtherNode();
signals:
	void fileStoppedSharing();
	void fileStartedSharing();
	void fileRequestsForSync(TextShredderPacket &);
};

#endif // SYNCABLEFILE_H
