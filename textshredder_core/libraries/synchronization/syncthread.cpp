#include "syncthread.h"

int SyncThread::sharedIndex = 1;

quint16 SyncThread::nextSyncThreadHandle = 1;

SyncThread::SyncThread(QObject * parent, QSharedPointer<TextShredderConnection>conn,
					   QSharedPointer< WorkingCopy> workingCopyPointer) :
	QObject(parent), connectionPointer(conn), workingCopyPointer(workingCopyPointer),
	shadowCopy(this), editList(NULL), timer(NULL),
	logging(this, QString("SyncThread").append(QString::number(sharedIndex)))
{
	WorkingCopy *wc = workingCopyPointer.data();
	wc->getContent();
	shadowCopy.setLogging(&logging);

	connectSignalsForConnection();
	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));

	qDebug("A");
	sourceSyncThreadHandle = nextSyncThreadHandle;
	qDebug() << nextSyncThreadHandle;
	qDebug() << sourceSyncThreadHandle;
	qDebug("B");
	nextSyncThreadHandle++;
}

void SyncThread::connectSignalsForConnection()
{
	qDebug("SyncThread::connectSignalsForConnection");
	connect(connectionPointer.data(), SIGNAL(incomingEditPacketContent(QByteArray&, quint16)), this, SLOT(receivedEditPacketContent(QByteArray&, quint16)));
	connect(connectionPointer.data(), SIGNAL(incomingFileDataPacketContent(QByteArray&, quint16)), this, SLOT(receivedFileDataPacketContent(QByteArray&, quint16)));
}

//For testing only
SyncThread::SyncThread(QObject * parent, QSharedPointer <WorkingCopy> newWorkingCopy) :
	QObject(parent), workingCopyPointer(newWorkingCopy),
	shadowCopy(this, *newWorkingCopy.data()->getContent()), editList(NULL), timer(NULL),
	logging(this)
{
	*(shadowCopy.getContent ()) = *workingCopyPointer.data()->getContent(); // set shadow copy
	shadowCopy.setLogging(&logging);
	syncThreadNumber = sharedIndex++;
}

void SyncThread::startSync()
{
	timer.start(WRITETHREAD_INTERVAL);
}

void SyncThread::receivedEditPacketContent(QByteArray &content, quint16 destination)
{
	if (sourceSyncThreadHandle == destination) {
		this->processChanges(content);
	}
}
void SyncThread::receivedFileDataPacketContent(QByteArray &content, quint16 destination)
{
	qDebug("SyncThread::receivedFileDataPacketContent");
	qDebug() << "Source : " << sourceSyncThreadHandle << " Destination " << destination;
	if (sourceSyncThreadHandle == destination) {
		qDebug() << "Should handle";
		this->receivedDownloadedContent(content);
	}
}

void SyncThread::processChanges(QByteArray & content)
{
	QString procesChangesMessage("SyncThread::processChanges");
	logging.writeLog (procesChangesMessage, DEBUG);
	EditList incomingEditList(this, content);
	this->applyReceivedEditList(incomingEditList);
}
void SyncThread::receivedDownloadedContent(QByteArray & content)
{
	qDebug("Received download content");
	QString string(content);
	workingCopyPointer.data()->setContent(string);
	shadowCopy.setContent(string);
	shadowCopy.getBackupCopy()->setContent(string);
	startSync();
}


void SyncThread::pushChanges()
{
	shadowCopy.lock();
	workingCopyPointer.data()->lock();

	QString *workingCopyContent = workingCopyPointer.data()->getContent();
	int shadowLocalVersion = shadowCopy.getLocalVersion();

	QList<Patch> newPatches = shadowCopy.getPatchesToConvertString (*workingCopyContent);
	if(newPatches.length() > 0) {
		Edit e(this, shadowLocalVersion, newPatches);
		editList.addEdit(e);
		QList<Edit> applyList;
		applyList.append(e);
		shadowCopy.applyLocalEdits(applyList);
	}

	writePacketOfEditList();
	workingCopyPointer.data()->unlock();
	shadowCopy.unlock();
}

void SyncThread::writePacketOfEditList()
{
	editList.lock();
	TextShredderPacket *newPacket = editList.getAllocatedPacket();
	editList.unlock();
	writePacketOnConnection(*newPacket);
	delete newPacket;
}

void SyncThread::writePacketOnConnection(TextShredderPacket &packet)
{
	qDebug() << connectionPointer.isNull();
	packet.getHeader().setConnectionHandle(destinationSyncThreadHandle);
	connectionPointer.data()->write(packet);
}

void SyncThread::applyReceivedEditList(EditList &incomingEditList)
{
	QString editListMessage("+ Received EditList, based on version: ");
	editListMessage += QString::number(incomingEditList.getRemoteVersion());
	logging.writeLog (editListMessage, DEBUG);
	editListMessage = "+ Received EditList contains ";
	editListMessage += QString::number(incomingEditList.getEdits().size());
	editListMessage += " edit(s)";
	logging.writeLog(editListMessage, DEBUG);

	shadowCopy.lock();
	workingCopyPointer.data()->lock();
	editList.lock ();
	int currentLocalVersion = shadowCopy.getLocalVersion ();
	int basedVersionOfIncommingEditList = incomingEditList.getRemoteVersion();

	if (basedVersionOfIncommingEditList < currentLocalVersion) {
		shadowCopy.revert();
	}

	QList<Edit> ackedEdits = editList.popEditsUpToLocalVersion(basedVersionOfIncommingEditList);
	if ((int)shadowCopy.getLocalVersion() < basedVersionOfIncommingEditList) {
		QString message("SyncT: sh.localversion < incomming based version");
		logging.writeLog(message);
		shadowCopy.applyLocalEdits(ackedEdits);
	}

	QList<Edit> receivedEdits = incomingEditList.getEdits();
	shadowCopy.applyEdits(receivedEdits);

	int count = 0;
	while (count < receivedEdits.count()) {
		Edit e = receivedEdits.at(count);
		workingCopyPointer.data()->applyPatches(e.getPatches());
		count++;
	}

	shadowCopy.backup();

	shadowCopy.applyLocalEdits(editList.getEdits());

	editList.updateToRemote(shadowCopy.getRemoteVersion());
	editList.unlock ();
	workingCopyPointer.data()->unlock();
	shadowCopy.unlock ();
}

void SyncThread::stop()
{
	timer.stop();
}

qint16 SyncThread::getLocalPort()
{
	return connectionPointer.data()->getLocalPort();
}

void SyncThread::setDestinationHandle(quint16 destination)
{
	destinationSyncThreadHandle = destination;
}

quint16 SyncThread::getDestinationHandle()
{
	return destinationSyncThreadHandle;
}

quint16 SyncThread::getSourceHandle()
{
	return sourceSyncThreadHandle;
}

void SyncThread::sendFileDataAndStart()
{
	QByteArray bytes;
	bytes.append(*workingCopyPointer.data()->getContent());
	qDebug() << "before" << destinationSyncThreadHandle;
	TextShredderPacket packet(this, kPacketTypeFileData, bytes, destinationSyncThreadHandle);
	qDebug("writePacketOnConnection(packet) - start");
	qDebug() << packet.getHeader().getConnectionHandle();
	writePacketOnConnection(packet);
	qDebug("writePacketOnConnection(packet) - done");
	startSync();
}
