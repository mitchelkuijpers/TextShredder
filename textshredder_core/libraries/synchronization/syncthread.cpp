#include "syncthread.h"


int SyncThread::sharedIndex = 1;

SyncThread::SyncThread(QObject * parent, int port, QString &address,
					   WorkingCopy & newWorkingCopy) :
	QObject(parent), connection(this, address, port, false), workingCopy(&newWorkingCopy),
	shadowCopy(this, *newWorkingCopy.getContent()), editList(NULL), timer(this),
        logging(this, QString("SyncThread ").append (QString::number (sharedIndex)))
{
	*(shadowCopy.getContent ()) = *workingCopy->getContent(); // set shadow copy
	shadowCopy.setLogging(&logging);

	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));

	connect(&connection, SIGNAL(incomingEditPacketContent(QByteArray&)),
			this, SLOT(processChanges(QByteArray&)));
	connect(&connection, SIGNAL(clientDisconnected()),
			this, SLOT(stop()));
	connect(&connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
			this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
	qDebug() << address << " " << port;
	connection.startConnection();
	syncThreadNumber = sharedIndex++;
}

SyncThread::SyncThread(QObject *parent, WorkingCopy &newWorkingCopy) :
		QObject(parent), connection(this), workingCopy(&newWorkingCopy),
		shadowCopy(this, *newWorkingCopy.getContent()), editList(NULL), timer(this),
		logging(this, QString("SyncThread ").append(QString::number(sharedIndex)))
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));
	connect(&connection, SIGNAL(incomingEditPacketContent(QByteArray&)),
			this, SLOT(processChanges(QByteArray&)));
	connect(&connection, SIGNAL(clientDisconnected()),
			this, SLOT(stop()));
	connect(&connection, SIGNAL(incomingFileDataPacketContent(QByteArray&)),
			this, SLOT(receivedDownloadedContent(QByteArray&)));

	syncThreadNumber = sharedIndex++;
}

void SyncThread::connectionStatusChanged(TextShredderConnectionStatus status) {
	qDebug("SyncThread::connectionStatusChanged");
	qDebug() << status;
	if (status == Connected) {
		connect(&connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
				this, SLOT(connectionStatusChanged(TextShredderConnectionStatus)));
		QByteArray packetContent;
		packetContent.append(*(workingCopy->getContent()));
		TextShredderPacket packet(this, kPacketTypeFileData, packetContent);
		connection.write(packet);

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
	workingCopy->lock();

	QString *workingCopyContent = workingCopy->getContent();
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
	workingCopy->unlock();
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
	connection.write(packet);
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
	workingCopy->lock();
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
		qDebug("Before apply patches");
		qDebug() << *workingCopy->getContent();
		workingCopy->applyPatches(e.getPatches());
		qDebug() << *workingCopy->getContent();
		qDebug("After apply patches");
		count++;
	}

	shadowCopy.backup();

	shadowCopy.applyLocalEdits(editList.getEdits());

	editList.updateToRemote(shadowCopy.getRemoteVersion());
	editList.unlock ();
	workingCopy->unlock();
	shadowCopy.unlock ();
}

void SyncThread::stop()
{
	timer.stop();
}

qint16 SyncThread::getLocalPort()
{
	return connection.getLocalPort();
}

void SyncThread::receivedDownloadedContent(QByteArray & content)
{
	qDebug("Received download content");
	QString string(content);
	qDebug() << string;
	workingCopy->setContent(string);
	shadowCopy.setContent(string);
	shadowCopy.getBackupCopy()->setContent(string);
	startSync();
}
