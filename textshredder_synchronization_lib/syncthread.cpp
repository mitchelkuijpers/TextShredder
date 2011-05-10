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
	shadowCopy.lock();
	int currentLocalVersion = shadowCopy.getLocalVersion ();
	int incomingLocalVersion = incomingEditList.getRemoteVersion();

	bool didRevert = false;
	if(incomingLocalVersion < currentLocalVersion) {
		shadowCopy.revert();
		didRevert = true;
	}

	QList<Edit> edits = incomingEditList.getEdits();
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
