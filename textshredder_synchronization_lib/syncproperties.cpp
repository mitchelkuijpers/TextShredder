#include "syncproperties.h"

SyncProperties::SyncProperties(QObject *parent, int socketDescriptor,
			   WorkingCopy *workingCopy) :
	QObject(parent), workingCopy(workingCopy), editList(this),
	textShredderSocket(this, socketDescriptor), shadowCopy(this)
{
	*(shadowCopy.getContent ()) = *workingCopy->getContent();
};

TextShredderSocket * SyncProperties::getSocket()
{
	return &textShredderSocket;
}

WorkingCopy * SyncProperties::getWorkingCopy()
{
	return workingCopy;
}


void SyncProperties::pushChanges()
{
	shadowCopy.lock();
	QString *shadowCopyContent = shadowCopy.getContent();
	int shadowLocalVersion = shadowCopy.getLocalVersion();

	workingCopy->lock();
	QList<Patch> newPatches = workingCopy->getPatchesToConvertString (*shadowCopyContent);
	editList.addEdit (Edit(this, shadowLocalVersion, newPatches));
	shadowCopy.processPatches(newPatches);

	editList.lock();
	TextShredderPacket *newPacket =editList.getAllocatedPacket();
	editList.unlock();

	textShredderSocket.writePacket (newPacket);

	workingCopy->unlock();
	shadowCopy.unlock();
	delete newPacket;
}

void SyncProperties::processChanges()
{
	TextShredderPacket *packet = textShredderSocket.readPacket();
	if (packet->isEditPacket()) {
		EditList incomingEditList(this, *packet);
		this->applyReceivedEditList(incomingEditList);
	}
}

void SyncProperties::applyReceivedEditList(EditList &incomingEditList)
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

