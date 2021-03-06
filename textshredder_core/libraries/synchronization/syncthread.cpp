#include "syncthread.h"
#include "../logging/textshredderlogging.cpp"

int SyncThread::sharedIndex = 1;

quint16 SyncThread::nextSyncThreadHandle = 1;

SyncThread::SyncThread(QObject * parent, QSharedPointer<TextShredderConnection>conn,
					   QSharedPointer< WorkingCopy> workingCopyPointer) :
	QObject(parent), connectionPointer(conn), workingCopyPointer(workingCopyPointer),
	shadowCopy(this), editList(NULL), timer(NULL),
	logging(this, QString("SyncThread").append(QString::number(sharedIndex))),
	performanceLog(this, QString("Performance").append(QString::number(sharedIndex)))
{
	WorkingCopy *wc = workingCopyPointer.data();
	shadowCopy.setContent(* wc->getContent());


	connectSignalsForSynchronization();

	connect(&editList, SIGNAL(editListEmpty()),
			this, SIGNAL(editListEmpty()));
	connect(&editList, SIGNAL(editListNotEmpty()),
			this, SIGNAL(editListNotEmpty()));

	sourceSyncThreadHandle = nextSyncThreadHandle;
	nextSyncThreadHandle++;
}

//For testing only
SyncThread::SyncThread(QObject * parent, QSharedPointer <WorkingCopy> newWorkingCopy) :
	QObject(parent), workingCopyPointer(newWorkingCopy),
	shadowCopy(this, *newWorkingCopy.data()->getContent()), editList(NULL), timer(NULL),
	logging(this), performanceLog(this)
{
	shadowCopy.setContent(*workingCopyPointer.data()->getContent()); // set shadow copy
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
void SyncThread::receivedFileDataPacket(TextShredderPacket &packet, quint16 destination)
{
	if (sourceSyncThreadHandle == destination) {
		this->destinationSyncThreadHandle = FileDataPacket::getConnectionHandle(packet);
		QByteArray fileData = FileDataPacket::getFileDataContent(packet);
		this->receivedDownloadedContent(fileData);
	}
}

void SyncThread::processChanges(QByteArray & content)
{
	QString procesChangesMessage("SyncThread::processChanges");
	logging.writeLog (procesChangesMessage, DEBUG);
	EditList *incomingEditList = EditListPacket::GetAllocatedEditListFromPacketContent(content);
	this->applyReceivedEditList(*incomingEditList);
	delete incomingEditList;

}
void SyncThread::receivedDownloadedContent(QByteArray & content)
{
	QString string(content);
	workingCopyPointer.data()->setContent(string);
	shadowCopy.setContent(string);
	shadowCopy.getBackupCopy().setContent(string);
	startSync();
}


void SyncThread::pushChanges()
{
	beforeLock();

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

	afterLock();
}

void SyncThread::writePacketOfEditList()
{
	editList.lock();
	EditListPacket newPacket(this, editList);
	//TextShredderPacket *newPacket = editList.getAllocatedPacket();
	editList.unlock();
	writePacketOnConnection(newPacket);
	//newPacket->deleteLater();
}

void SyncThread::writePacketOnConnection(TextShredderPacket &packet)
{
	qDebug() << "SyncThread::writePacketOnConnection connectionPointer.isNull = " << connectionPointer.isNull();
	packet.getHeader().setConnectionHandle(destinationSyncThreadHandle);
	connectionPointer.data()->write(packet);
}

void SyncThread::applyReceivedEditList(EditList &incomingEditList)
{
	beforeLock();

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

	editList.setRemoteVersion(shadowCopy.getRemoteVersion());
	editList.unlock ();
	workingCopyPointer.data()->unlock();
	shadowCopy.unlock ();

	afterLock();
}

void SyncThread::receivedEndSynchronizationPacket(quint16 destination) {
	if	(destination == sourceSyncThreadHandle) {
		breakDownSynchronization();
		emit syncThreadStoppedByOtherNode();
		qDebug("TODO: SyncThread::receivedEndSynchronizationPacket -> Emit sync stopped ");
	}
}

void SyncThread::stopSync()
{
	breakDownSynchronization();
	EndSynchronizationPacket packet(this, destinationSyncThreadHandle);
	writePacketOnConnection(packet);
}

void SyncThread::breakDownSynchronization()
{
	timer.stop();
	disconnectSignalsForSynchronization();
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
	//TextShredderPacket packet(this, kPacketTypeFileData, bytes, destinationSyncThreadHandle);
	FileDataPacket packet(this, bytes, sourceSyncThreadHandle);
	packet.getHeader().setConnectionHandle(destinationSyncThreadHandle);

	qDebug("writePacketOnConnection(packet) - start");
	qDebug() << packet.getHeader().getConnectionHandle();
	writePacketOnConnection(packet);
	qDebug("writePacketOnConnection(packet) - done");
	startSync();
}

void SyncThread::connectSignalsForSynchronization()
{
	qDebug("SyncThread::connectSignalsForSynchronization");
	connect(connectionPointer.data(), SIGNAL(clientDisconnected()), this, SLOT(deleteLater()));
	connect(connectionPointer.data(), SIGNAL(incomingEditPacketContent(QByteArray&, quint16)), this, SLOT(receivedEditPacketContent(QByteArray&, quint16)));
	connect(connectionPointer.data(), SIGNAL(incomingFileDataPacket(TextShredderPacket&, quint16)), this, SLOT(receivedFileDataPacket(TextShredderPacket &, quint16)));
	connect(connectionPointer.data(), SIGNAL(incomingEndSynchronizationPacket(quint16)), this, SLOT(receivedEndSynchronizationPacket(quint16)));
	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));
	connect(this, SIGNAL(addToAverageLockTime(uint)), PerformanceCalculator::Instance(), SLOT(addNewLockTime(uint)));
}

void SyncThread::disconnectSignalsForSynchronization()
{
	qDebug("SyncThread::disconnectSignalsForSynchronization");
	if(!connectionPointer.isNull()){
		disconnect(connectionPointer.data(), SIGNAL(clientDisconnected()), this, SLOT(deleteLater()));
		disconnect(connectionPointer.data(), SIGNAL(incomingEditPacketContent(QByteArray&, quint16)), this, SLOT(receivedEditPacketContent(QByteArray&, quint16)));
		disconnect(connectionPointer.data(), SIGNAL(incomingFileDataPacket(TextShredderPacket&, quint16)), this, SLOT(receivedFileDataPacket(TextShredderPacket &, quint16)));
		disconnect(connectionPointer.data(), SIGNAL(incomingEndSynchronizationPacket(quint16)), this, SLOT(receivedEndSynchronizationPacket(quint16)));
		disconnect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));
	}
}

void SyncThread::beforeLock()
{
	if(performanceTime.isNull()) {
		performanceTime.start();
	} else {
		performanceTime.restart();
	}
}

void SyncThread::afterLock()
{
	unsigned int milliseconds = performanceTime.elapsed();
	emit addToAverageLockTime(milliseconds);
}
