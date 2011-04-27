#include "syncablefile.h"

#define kDefaultFileAlias QString("untitled.txt")

SyncableFile::SyncableFile(QObject *parent) : QObject(parent)
{
	fileAlias = kDefaultFileAlias;
	filePath = "";
	fileType = FileTypeTXT;
	workingCopy = new WorkingCopy(this);
	QString workingCopyContent;
	workingCopy->setContent(workingCopyContent);
}

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

bool SyncableFile::hasClientWithName(QString &name)
{
	for (int i = 0; i < clients.size(); ++i) {
		if (clients.at(i) == name) {
			return true;
		}
	}
	return false;
}

bool SyncableFile::addClientWithName(QString &name)
{	
	if(hasClientWithName(name)) {
		return false;
	}

	clients.append(name);
	notifyAvailableClientsChanged();

	return true;
}

bool SyncableFile::removeClientWithName(QString &name)
{
	if(hasClientWithName(name)) {
		clients.removeOne(name);
		notifyAvailableClientsChanged();
		return true;
	}
	return false;
}

bool SyncableFile::changeClientName(QString &name, QString &toName)
{
	if(QString::compare(name,toName,Qt::CaseInsensitive) == 0) {
		return false;
	}

	if(clients.indexOf(name) != -1 ) {
		clients.replace(clients.indexOf(name), toName);
	}
	return true;
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

QString & SyncableFile::getFileAlias()
{
	return fileAlias;
}
