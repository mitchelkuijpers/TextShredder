#include "syncablefile.h"

#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"
#include "../../../client/client.h"
#define kDefaultFileAlias QString("untitled.txt")

SyncableFile::SyncableFile(QObject *parent, QString &path) :
		QObject(parent), fileIdentifier(QUuid::createUuid().toString()), filePath(path), shared(false), opened(false)
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
	QObject(parent), fileIdentifier(identifier), fileAlias(alias), workingCopy(NULL), shared(false), opened(false)
{
	fileType = FileTypeTXT;
	workingCopy = QSharedPointer<WorkingCopy>(new WorkingCopy(this));
}

SyncableFile::SyncableFile(QObject *parent, QString &alias, FileType type) :
	QObject(parent), fileAlias(alias), workingCopy(NULL), fileType(type), shared(false), opened(false)
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

bool SyncableFile::isOpened()
{
	return opened;
}

void SyncableFile::close()
{
	opened = false;
}

void SyncableFile::open()
{
	opened = true;
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
			qDebug("TODO: SyncableFile::setShared only do when server");
			for (int i = 0; i < syncThreads.count(); i++) {
				QSharedPointer<SyncThread> thread = syncThreads.at(i);
				thread.data()->stopSync();
			}
			emit fileStoppedSharing();
		}
	}
}

void SyncableFile::stopSync()
{

}

void SyncableFile::requestSync()
{
	QSharedPointer<SyncThread> newThread =
			QSharedPointer<SyncThread>(new SyncThread(this, Client::Instance().data()->getConnection() , workingCopy));

	syncThreads.append(newThread);
	qDebug() << "Handle = " <<  newThread.data()->getSourceHandle();
	FileRequestPacket packet(this, newThread.data()->getSourceHandle(), fileIdentifier);
	quint16 value = FileRequestPacket::getSourceHandle(packet);
	qDebug() << "value " << value;
	qDebug() << "other " << packet.getHeader().getConnectionHandle();
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

void SyncableFile::startSyncOn(quint16 destination,
							   QSharedPointer<TextShredderConnection> connection)
{
	QSharedPointer<SyncThread> sync = QSharedPointer<SyncThread>(
				new SyncThread(this, connection, this->workingCopy));
	sync.data()->setDestinationHandle(destination);
	sync.data()->sendFileDataAndStart();
	syncThreads.append(sync);
}
