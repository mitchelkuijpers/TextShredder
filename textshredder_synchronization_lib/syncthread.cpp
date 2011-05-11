#include "syncthread.h"

int SyncThread::sharedIndex = 1;

SyncThread::SyncThread(QObject * parent, TextShredderConnection & newConnection,
					   WorkingCopy & newWorkingCopy) :
	QObject(parent), connection(&newConnection), workingCopy(&newWorkingCopy),
	shadowCopy(this), editList(NULL), timer(this),
        logging(this, QString("SyncThread ").append (QString::number (sharedIndex)))
{
	*(shadowCopy.getContent ()) = *workingCopy->getContent(); // set shadow copy
	shadowCopy.setLogging(&logging);
	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));

	connect(connection, SIGNAL(incomingEditPacketContent(QByteArray&)),
			this, SLOT(processChanges(QByteArray&)));
	connect(connection, SIGNAL(clientDisconnected()),
			this, SLOT(stop()));

	syncThreadNumber = sharedIndex++;
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

	QString *shadowCopyContent = workingCopy->getContent();
	int shadowLocalVersion = shadowCopy.getLocalVersion();

	QList<Patch> newPatches = shadowCopy.getPatchesToConvertString (*shadowCopyContent);
	if(newPatches.length() > 0) {
		editList.addEdit (Edit(this, shadowLocalVersion, newPatches));
		shadowCopy.processPatches(newPatches);
		shadowCopy.setLocalVersion (shadowCopy.getLocalVersion ()+1);
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
	connection->write(packet);
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
	int currentLocalVersion = shadowCopy.getLocalVersion ();
	int basedVersionOfIncommingEditList = incomingEditList.getRemoteVersion();

	QString currentLocalVersionOfShadow("+ Current local shadow version: ");
	currentLocalVersionOfShadow += QString::number(currentLocalVersion);
	logging.writeLog(currentLocalVersionOfShadow, DEBUG);

	bool didRevert = false;
	if(basedVersionOfIncommingEditList < currentLocalVersion) {
		if (basedVersionOfIncommingEditList > (int) shadowCopy.getBackupCopy()->getLocalVersion()) {
			QList<Edit> applyBackupEdits = editList.getEditsUpToLocalVersion(basedVersionOfIncommingEditList);

			for(int i = 0; i < applyBackupEdits.count(); i++) {
				Edit e = applyBackupEdits.at(i);
				shadowCopy.getBackupCopy()->applyPatches(e.getPatches ());
			}
			shadowCopy.getBackupCopy ()->setLocalVersion(basedVersionOfIncommingEditList);
		}

		QString revertMessage("+ Will revert");
		logging.writeLog(revertMessage, DEBUG);
		shadowCopy.revert();
		didRevert = true;
	}

	QList<Edit> edits = incomingEditList.getEdits();
	int count = 0;
	while(count < edits.size()) {
		Edit e = edits[count];
		QString editString = e.toString();
		logging.writeLog(editString, DEBUG);
		count++;
	}
	if (count == 0) {
		QString noEditsMessage("No edits in this editlist");
		logging.writeLog(noEditsMessage, DEBUG);
	}
	QString gotHere("Here");
	logging.writeLog (gotHere);
	shadowCopy.applyEdits(edits);

	workingCopy->lock();

	for (int i = 0; i < edits.size(); i++) {
		Edit e = edits.at(i);
		QList<Patch> patches = e.getPatches();
		workingCopy->applyPatches (patches);
	}

	shadowCopy.backup();

	if (didRevert) {
		editList.lock();
		QList<Edit> edits = editList.getEdits();
		int i = 0;
		while ( i < edits.size() ) {
			Edit e = edits.at (i);
			shadowCopy.processPatches(e.getPatches ());
			i++;
		}
		editList.unlock();
	}
	int currentKnownRemoteVersion = shadowCopy.getRemoteVersion();
	int currentKnownLocalVersion = shadowCopy.getLocalVersion();

	editList.lock ();
	editList.updateToRemoteAndLocalVersion(currentKnownRemoteVersion,
											currentKnownLocalVersion);
	editList.unlock ();

	workingCopy->unlock();
	shadowCopy.unlock ();
}

void SyncThread::stop()
{
	timer.stop();
}
