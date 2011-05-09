#include "syncthread.h"

int SyncThread::sharedIndex = 1;

SyncThread::SyncThread(QObject * parent, TextShredderConnection & newConnection,
					   WorkingCopy & newWorkingCopy) :
	QObject(parent), connection(&newConnection), workingCopy(&newWorkingCopy),
	shadowCopy(this), editList(this), timer(this)
{
	*(shadowCopy.getContent ()) = *workingCopy->getContent(); // set shadow copy

	connect(&timer, SIGNAL(timeout()), this, SLOT(pushChanges()));

	connect(connection, SIGNAL(incomingEditPacketContent(QByteArray&)),
			this, SLOT(processChanges(QByteArray&)));
	connect(connection, SIGNAL(clientDisconnected()),
			this, SLOT(stop()));
	timer.start(WRITETHREAD_INTERVAL);

	syncThreadNumber = sharedIndex++;
	QString name("SyncThread ");
	name.append (QString::number (syncThreadNumber));
	outgoingLog = new TextShredderLogging(this, name + QString("(out)"));
	incommingLog = new TextShredderLogging(this, name + QString("(in)"));
}

void SyncThread::processChanges(QByteArray & content)
{
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
		outgoingLog->writeLog ("We have new local edits");
		editList.addEdit (Edit(this, shadowLocalVersion, newPatches));
		shadowCopy.processPatches(newPatches);
		shadowCopy.setLocalVersion (shadowCopy.getLocalVersion ()+1);
	} else {
		outgoingLog->writeLog ("We DO NOT have new local edits");
	}
	editList.lock();
	QList<Edit> edits = editList.getEdits ();
	for (int i = 0; i< edits.size (); i++) {
		Edit e = edits.at (i);
		outgoingLog->writeLog("Next edit in list");
		outgoingLog->writeLog(((Patch)e.getPatches ().at (0)).toString ().toStdString ().c_str());
	}
	TextShredderPacket *newPacket = editList.getAllocatedPacket();
	editList.unlock();
	connection->write(*newPacket);
	delete newPacket;
	workingCopy->unlock();
	shadowCopy.unlock();
}

void SyncThread::applyReceivedEditList(EditList &incomingEditList)
{
	shadowCopy.lock();
	int currentLocalVersion = shadowCopy.getLocalVersion ();
	int incomingLocalVersion = incomingEditList.getRemoteVersion();

	QString incomRemVer("Incomming Remote Version ");
	incomRemVer.append (QString::number (incomingLocalVersion));
	incommingLog->writeLog (incomRemVer.toStdString ().c_str ());
	QString curLocalVer("Current Local Version ");
	curLocalVer.append (QString::number (currentLocalVersion));
	incommingLog->writeLog (curLocalVer.toStdString ().c_str ());

	bool didRevert = false;
	if(incomingLocalVersion < currentLocalVersion) {
		incommingLog->writeLog ("Have to do revert");
		shadowCopy.revert();
		didRevert = true;
		//editList.lock();
		//editList.empty();
		//editList.unlock();
	}

	QList<Edit> edits = incomingEditList.getEdits();
	shadowCopy.applyEdits(edits);

	workingCopy->lock();
	incommingLog->writeLog ("Will process edits");
	for (int i = 0; i < edits.size(); i++) {
		Edit e = edits.at(i);
		QList<Patch> patches = e.getPatches();
		for(int j=0; j < patches.count(); j++) {
			Patch p = patches.at (j);
			incommingLog->writeLog (p.toString ().toStdString ().c_str ());
		}
		workingCopy->applyPatches (patches);
	}

	shadowCopy.backup();

	if (didRevert) {
		editList.lock();
		QList<Edit> edits = editList.getEdits();
		int i = 0;
		while (i < edits.size ()) {
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
