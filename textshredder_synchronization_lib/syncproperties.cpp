#include "syncproperties.h"

SyncProperties::SyncProperties(QObject *parent, int socketDescriptor,
			   WorkingCopy * workingCopy) :
	QObject(parent), workingCopy(workingCopy), editList(this),
	textShredderSocket(this, socketDescriptor), shadowCopy(this)
{

};

TextShredderSocket * SyncProperties::getSocket()
{
	return &textShredderSocket;
}

WorkingCopy * SyncProperties::getWorkingCopy()
{
	return workingCopy;
}


void SyncProperties::pushChanges() {

}

void SyncProperties::applyReceivedEditList(EditList &editList)
{

}

