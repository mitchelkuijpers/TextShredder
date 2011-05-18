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

	bool hasClientWithName(QString &name);
	bool addClientWithName(QString &name);
	bool removeClientWithName(QString &name);
	bool changeClientName(QString &name, QString &toName);

	void stopSync();
	WorkingCopy * getWorkingCopy();
	QString & getFileAlias();
	QString & getFileIdentifier();

	bool isShared();
	void setShared(bool share);

	void requestSync();
	void createSynchronizationWithPortAndAddress(quint16 port, QString &hostName);

	static void doDeleteLater(SyncableFile *obj);
private:
	QString fileIdentifier;
	FileType typeForSuffix(QString &suffix);
	QString filePath;
	QString fileAlias;
	WorkingCopy *workingCopy;
	FileType fileType;
	bool shared;

	QList<SyncThread *> syncThreads;

signals:
	void fileStoppedSharing();
	void fileStartedSharing();
	void fileRequestsForSync(TextShredderPacket &);
};

#endif // SYNCABLEFILE_H
