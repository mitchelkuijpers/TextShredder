#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"

#define kDefaultFileAlias QString("untitled.txt")

SyncableFile::SyncableFile(QObject *parent, QString &path) :
		QObject(parent), fileIdentifier(QUuid::createUuid().toString()), filePath(path), shared(false)
{
	QFileInfo fileInfo(path);
	fileAlias = fileInfo.fileName();
	QString suffix(fileInfo.suffix ());
	fileType = typeForSuffix(suffix);

	workingCopy = QSharedPointer<WorkingCopy>(new WorkingCopy(this));

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QString contentString(file.readAll());
	workingCopy->setContent(contentString);
}

SyncableFile::SyncableFile(QObject *parent, QString &identifier, QString &alias) :
	QObject(parent), fileIdentifier(identifier), fileAlias(alias), workingCopy(NULL)
{
	fileType = FileTypeTXT;
	workingCopy = QSharedPointer<WorkingCopy>(new WorkingCopy(this));
}

SyncableFile::SyncableFile(QObject *parent, QString &alias, FileType type) :
	QObject(parent), fileAlias(alias), workingCopy(NULL), fileType(type)
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
	this->fileIdentifier = other.fileIdentifier;
	this->fileAlias = other.fileAlias;
	this->filePath = other.filePath;
	this->shared = other.shared;
	this->fileType = other.fileType;
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

QSharedPointer<WorkingCopy> SyncableFile::getWorkingCopy()
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
	qDebug("Set syncable file shared");
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
	QSharedPointer<SyncThread> newThread = QSharedPointer<SyncThread>(new SyncThread(this, this->workingCopy));
	syncThreads.append(newThread);

	FileRequestPacket packet(newThread.data()->getSourceHandle(), fileIdentifier);
	emit fileRequestsForSync(packet);
	qDebug("Create socket SyncableFile::requestSync");
}

void SyncableFile::doDeleteLater(SyncableFile *obj)
{
	obj->deleteLater();
}

void SyncableFile::setFileAlias(QString & newFileAlias)
{
	this->fileAlias = newFileAlias;
}

QSharedPointer<WorkingCopy> SyncableFile::openWorkingCopyForGUI()
{
	return workingCopy;
}

void SyncableFile::closeWorkingCopyFromGUI()
{
}
