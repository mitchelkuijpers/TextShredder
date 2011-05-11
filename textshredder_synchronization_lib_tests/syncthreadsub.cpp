#include "syncthreadsub.h"

SyncThreadSub::SyncThreadSub(QObject *parent, TextShredderConnection & newConnection,
                             WorkingCopy & newWorkingCopy) :
        SyncThread(parent, newConnection, newWorkingCopy)
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

void SyncThreadSub::writePacketOfEditList()
{
    SyncThread::writePacketOfEditList();
}


