#include "syncablefile.h"

#define kDefaultFileAlias QString("untitled.txt")

SyncableFile::SyncableFile(QObject *parent, QString &path) :
		QObject(parent), fileIdentifier(QUuid::createUuid().toString()), filePath(path)
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

SyncableFile::SyncableFile(QObject *parent, QString &identifier, QString &alias) :
	QObject(parent), fileIdentifier(identifier), fileAlias(alias)
{
	fileType = FileTypeTXT;
}

SyncableFile::SyncableFile(QObject *parent, QString &alias, FileType type) :
	QObject(parent), fileAlias(alias), fileType(type)
{

}

SyncableFile::SyncableFile(const SyncableFile &other) : QObject(this)
{
	this->fileIdentifier = other.fileIdentifier;
	this->fileAlias = other.fileAlias;
	this->filePath = other.filePath;
	this->shared = other.shared;
	this->fileType = other.fileType;
	this->workingCopy = other.workingCopy;
}

bool SyncableFile::operator == (const SyncableFile & other)
{
	return (this->fileIdentifier == other.fileIdentifier);
}

SyncableFile & SyncableFile::operator=(const SyncableFile & other)
{
	qDebug("1");
	this->fileIdentifier = other.fileIdentifier;
	qDebug("2");
	this->fileAlias = other.fileAlias;
	qDebug("3");
	this->filePath = other.filePath;
	qDebug("4");
	this->shared = other.shared;
	qDebug("5");
	this->fileType = other.fileType;
	qDebug("6");
	this->workingCopy = other.workingCopy;
	return *this;
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

WorkingCopy * SyncableFile::getWorkingCopy()
{
	return workingCopy;
}

QString & SyncableFile::getFileAlias()
{
	return fileAlias;
}

QString & SyncableFile::getFileIdentifier()
{
	return fileIdentifier;
}

bool SyncableFile::isShared()
{
	return shared;
}

void SyncableFile::setShared(bool share)
{
	if (share != shared) {
		shared = share;
		if (shared) {
			emit fileStartedSharing();
		} else {
			emit fileStoppedSharing();
		}
	}
}

void SyncableFile::stopSync()
{

}

void SyncableFile::requestSync()
{
	SyncThread *newThread = new SyncThread(this, *this->workingCopy);
	syncThreads.append(newThread);
	FileRequestPacket packet(this, newThread->getLocalPort(), fileAlias);
	emit fileRequestsForSync(packet);
	qDebug("Create socket SyncableFile::requestSync");
}

void SyncableFile::createSynchronizationWithPortAndAddress(quint16 port, QString &hostName)
{
	qDebug("Should do some sync creation");
	SyncThread *newThread = new SyncThread(this, port, hostName, *workingCopy);
	syncThreads.append(newThread);
}
