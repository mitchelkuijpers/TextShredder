#include "readthread.h"

ReadThread::ReadThread(QObject *parent, SyncProperties *syncProperties) :
    QThread(parent), syncProperties(syncProperties)
{
}

void ReadThread::run()
{
}
