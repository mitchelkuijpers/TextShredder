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
}

void SyncThread::connectSignalsForConnection()
{
	connect(connectionPointer.data(), SIGNAL(incomingEditPacketContent(QByteArray&)),
			this, SLOT(processChanges(QByteArray&)));
	connect(connectionPointer.data(), SIGNAL(clientDisconnected()),
			this, SLOT(stop()));
	connect(connectionPointer.data(), SIGNAL(statusChanged(TextShredderConnectionStatus)),
			this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
}

SyncThread::SyncThread(QObject * parent, QSharedPointer <WorkingCopy> newWorkingCopy) :
	QObject(parent), workingCopyPointer(newWorkingCopy),
	shadowCopy(this, *newWorkingCopy.data()->getContent()), editList(NULL), timer(NULL),
	logging(this)
{
	*(shadowCopy.getContent ()) = *workingCopyPointer.data()->getContent(); // set shadow copy
	shadowCopy.setLogging(&logging);
	syncThreadNumber = sharedIndex++;
}

//SyncThread::SyncThread(QObject *parent, WorkingCopy &newWorkingCopy) :
//		QObject(parent), connection(this), workingCopy(&newWorkingCopy),
//		shadowCopy(this, *newWorkingCopy.getContent()), editList(NULL), timer(this),
//		logging(this, QString("SyncThread ").append(QString::number(sharedIndex)))
//{
//	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));
//	connect(&connection, SIGNAL(incomingEditPacketContent(QByteArray&)),
//			this, SLOT(processChanges(QByteArray&)));
//	connect(&connection, SIGNAL(clientDisconnected()),
//			this, SLOT(stop()));
//	connect(&connection, SIGNAL(incomingFileDataPacketContent(QByteArray&)),
//			this, SLOT(receivedDownloadedContent(QByteArray&)));

//	syncThreadNumber = sharedIndex++;
//}

void SyncThread::connectionStatusChanged(TextShredderConnectionStatus status) {
	qDebug("SyncThread::connectionStatusChanged");
	qDebug() << status;
	if (status == Connected) {
		connect(connectionPointer.data(), SIGNAL(statusChanged(TextShredderConnectionStatus)),
				this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
		QByteArray packetContent;
		packetContent.append(*(workingCopyPointer.data()->getContent()));
		TextShredderPacket packet(this, kPacketTypeFileData, packetContent);
		connectionPointer.data()->write(packet);

		startSync();
	}
}

void SyncThread::startSync()
{
	timer.start(WRITETHREAD_INTERVAL);
}

void SyncThread::processChanges(QByteArray & content)
{

	QString procesChangesMessage("SyncThread::processChanges");
	logging.writeLog (procesChangesMessage, DEBUG);
	EditList incomingEditList(this, content);
	this->applyReceivedEditList(incomingEditList);

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

void SyncThread::receivedDownloadedContent(QByteArray & content)
{
	qDebug("Received download content");
	QString string(content);
	workingCopyPointer.data()->setContent(string);
	shadowCopy.setContent(string);
	shadowCopy.getBackupCopy()->setContent(string);
	startSync();
}

void SyncThread::setDestinationHandle(quint16 destination)
{

}

quint16 SyncThread::getDestinationHandle()
{

}

quint16 SyncThread::getSourceHandle()
{

}
