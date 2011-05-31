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

	//If client, stop the syncthread -> remove all from list after stop
	if (!onServer) {
		stopSync();
		if (!isShared()) {
			emit syncableFileShouldBeRemoved();
		}
	}
	emit syncableFileChanged();
}

void SyncableFile::open()
{
	opened = true;
	emit syncableFileChanged();
	if (!onServer) {
		requestSync();
	}
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
			if (onServer) {
				qDebug() << "Stop Syncing on server";
				stopSync();
				qDebug() << "SyncableFile::setShared " << "//Evaluate this save";
				saveFileToPath();
				syncThreads.clear();
			}
			emit fileStoppedSharing();
		}
	}
	emit syncableFileChanged();
}

void SyncableFile::stopSync()
{
	qDebug() << "syncTreads.count" << syncThreads.count();
	for(int i = 0; i < syncThreads.count(); i++ ) {
		QSharedPointer<SyncThread> syncPointer = syncThreads.at(i);
		syncPointer.data()->stopSync();
	}
	syncThreads.clear();
}

void SyncableFile::requestSync()
{
	QSharedPointer<SyncThread> newThread =
			QSharedPointer<SyncThread>(new SyncThread(this, Client::Instance().data()->getConnection() , workingCopy));

	connect(newThread.data(), SIGNAL(syncThreadStoppedByOtherNode()), this, SLOT(syncThreadIsStoppedByOtherNode()));
	syncThreads.append(newThread);
	FileRequestPacket packet(this, newThread.data()->getSourceHandle(), fileIdentifier);
	emit fileRequestsForSync(packet);
	emit syncableFileChanged();
}

void SyncableFile::setFileAlias(QString & newFileAlias)
{
	this->fileAlias = newFileAlias;
}

void SyncableFile::startSyncOn(quint16 destination,
							   QSharedPointer<TextShredderConnection> connection)
{
	QSharedPointer<SyncThread> sync = QSharedPointer<SyncThread>(
				new SyncThread(this, connection, this->workingCopy));
	connect(sync.data(), SIGNAL(syncThreadStoppedByOtherNode()), this, SLOT(syncThreadIsStoppedByOtherNode()));

	sync.data()->setDestinationHandle(destination);
	sync.data()->sendFileDataAndStart();
	syncThreads.append(sync);
	emit syncableFileChanged();
}

void SyncableFile::syncThreadIsStoppedByOtherNode()
{
	for(int i = 0; i < syncThreads.count(); i++ ) {
		QSharedPointer<SyncThread> syncPointer = syncThreads.at(i);
		if (syncPointer.data() == sender()) {
			syncThreads.removeAt(i);
			if( isOpened() && !onServer ) {
				emit fileShouldNotifyEndOfSharing();
			}
			break;
		}
	}
	if (onServer && syncThreads.count() == 0) {
		saveFileToPath();
	}

	emit syncableFileChanged();
}

void SyncableFile::saveFileToPath()
{
	fileShouldBeBackedUp();
}

bool SyncableFile::isOnServer()
{
	return onServer;
}
void SyncableFile::setOnServer(bool value)
{
	onServer = value;
}

SyncableFileStatus SyncableFile::calculateStatus()
{
	if (syncThreads.count() > 0) {
		return Syncing;
	} else if (!onServer && isShared() && !opened) {
		return UnopenedSharedFile;
	} else if (onServer && isShared() && !opened) {
		return UnopenedSharedFile;
	} else if (!onServer && !isShared() && !opened) {
		//Should not happen
	} else if (onServer && !isShared() && !opened) {
		return Unshared;
	} else if (!onServer && isShared() && opened) {
		return Syncing;
	} else if (onServer && isShared() && opened) {
		return Editing;
	} else if (!onServer && !isShared() && opened) {
		return Offline;
	} else if (onServer && !isShared() && opened) {
		return Editing;
	}
	return Unknown;
}
