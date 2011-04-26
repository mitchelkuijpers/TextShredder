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

	/**
	  * Will change the file type for the SyncableFile
	  */
	void changeFileType(FileType type);

private:
	FileType typeForSuffix(QString &suffix);
	QString filePath;
	QString fileAlias;
	WorkingCopy *workingCopy;
	FileType fileType;
};

#endif // SYNCABLEFILE_H
