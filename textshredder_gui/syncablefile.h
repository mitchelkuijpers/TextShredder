#ifndef SYNCABLEFILE_H
#define SYNCABLEFILE_H

#include <QObject>
#include "../textshredder_synchronization_lib/workingcopy.h"

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
	explicit SyncableFile(QObject *parent, QString &path);
	explicit SyncableFile(QObject *parent, QString &path, QString &alias);
	SyncableFile(QObject *parent);

	/**
	  * Will change the file type for the SyncableFile
	  */
	void changeFileType(FileType type);

	bool hasClientWithName(QString &name);
	bool addClientWithName(QString &name);
	bool removeClientWithName(QString &name);
	bool changeClientName(QString &name, QString &toName);

	WorkingCopy * getWorkingCopy();
	QList<QString> & getAvailableClients();
	QString & getFileAlias();


private:
	FileType typeForSuffix(QString &suffix);
	QString filePath;
	QString fileAlias;
	WorkingCopy *workingCopy;
	FileType fileType;
	QList<QString> clients;

	void notifyAvailableClientsChanged();

signals:
	void availableClientsChanged();
};

#endif // SYNCABLEFILE_H
