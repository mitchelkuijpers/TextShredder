#include "syncthread.h"

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
}

void SyncThread::processChanges(QByteArray & content)
{
	EditList incomingEditList(this, content);
	this->applyReceivedEditList(incomingEditList);
}


void SyncThread::pushChanges()
{
	shadowCopy.lock();
	QString *shadowCopyContent = shadowCopy.getContent();
	int shadowLocalVersion = shadowCopy.getLocalVersion();

	workingCopy->lock();
	QList<Patch> newPatches = workingCopy->getPatchesToConvertString (*shadowCopyContent);
	editList.addEdit (Edit(this, shadowLocalVersion, newPatches));
	shadowCopy.processPatches(newPatches);

	editList.lock();
	TextShredderPacket *newPacket = editList.getAllocatedPacket();
	editList.unlock();

	connection->write(*newPacket);

	workingCopy->unlock();
	shadowCopy.unlock();
	delete newPacket;
}

void SyncThread::applyReceivedEditList(EditList &incomingEditList)
{
	shadowCopy.lock();
	int currentLocalVersion = shadowCopy.getLocalVersion ();
	int incomingLocalVersion = incomingEditList.getRemoteVersion();

	if(incomingLocalVersion < currentLocalVersion) {
		shadowCopy.revert();
		editList.lock();
		editList.empty();
		editList.unlock();
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
