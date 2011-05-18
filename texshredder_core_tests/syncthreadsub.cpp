#include "syncthreadsub.h"

SyncThreadSub::SyncThreadSub(QObject *parent, WorkingCopy & newWorkingCopy) :
		SyncThread(parent, newWorkingCopy)
{
}

void SyncThreadSub::processChanges(QByteArray &content)
{
    SyncThread::processChanges(content);
}

void SyncThreadSub::pushChanges()
{
    SyncThread::pushChanges();
}

void SyncThreadSub::startSync()
{
	//Should be empty
}

void SyncThreadSub::writePacketOfEditList()
{

}

EditList * SyncThreadSub::getEditList()
{
	return &(this->editList);
}

WorkingCopy * SyncThreadSub::getWorkingCopy()
{
	return this->workingCopy;
}

ShadowCopy * SyncThreadSub::getShadowCopy()
{
	return &(this->shadowCopy);
}

