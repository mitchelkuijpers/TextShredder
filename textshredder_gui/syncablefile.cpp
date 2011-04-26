#include "syncablefile.h"

SyncableFile::SyncableFile(QObject *parent, QString &path) :
	QObject(parent), filePath(path)
{
	QFileInfo fileInfo(path);
	fileAlias = fileInfo.fileName();
	QString suffix(fileInfo.suffix ());
	fileType = typeForSuffix(suffix);

	workingCopy = new WorkingCopy(this);

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QString contentString(file.readAll());
	workingCopy->setContent(contentString);
}

SyncableFile::SyncableFile(QObject *parent, QString &path, QString &alias) :
	QObject(parent), filePath(path), fileAlias(alias)
{
	QFileInfo fileInfo(path);
	QString suffix(fileInfo.suffix ());
	fileType = typeForSuffix(suffix);
}

void SyncableFile::changeFileType(FileType type)
{
	fileType = type;
}

FileType SyncableFile::typeForSuffix(QString &suffix)
{
	QString lowerCase(suffix.toLower());
	if (lowerCase == "php") {
		return FileTypePHP;
	} else if (lowerCase == "txt") {
		return FileTypeTXT;
	} else if (lowerCase == "html") {
		return FileTypeHTML;
	}
	return FileTypeUNKNOWN;
}

void SyncableFile::addClientWithName(QString &name)
{
	clients.append(name);
	notifyAvailableClientsChanged();
}

void SyncableFile::notifyAvailableClientsChanged()
{
	emit availableClientsChanged();
}

QList<QString> & SyncableFile::getAvailableClients()
{
	return clients;
}

WorkingCopy * SyncableFile::getWorkingCopy()
{
	return workingCopy;
}
