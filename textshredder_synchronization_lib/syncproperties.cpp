#include "syncproperties.h"

SyncProperties::SyncProperties(QObject *parent, int socketDescriptor,
			   WorkingCopy * workingCopy) :
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

}

void SyncProperties::applyReceivedEditList(EditList &incomingEditList)
{
	shadowCopy.lock();
	int currentLocalVersion = shadowCopy.getLocalVersion ();
	int incommingLocalVersion = incomingEditList.getRemoteVersion();

	if(incommingLocalVersion < currentLocalVersion) {
		shadowCopy.revert();
		editList.lock();
		editList.empty();
		editList.unlock();
	}
}

