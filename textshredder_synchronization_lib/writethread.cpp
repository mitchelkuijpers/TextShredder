#include "writethread.h"

WriteThread::WriteThread(QObject *parent, SyncProperties *syncProperties) :
    QThread(parent), syncProperties(syncProperties)
{
}

void WriteThread::run()
{
}
