#include "syncthread.h"

SyncThread::SyncThread(QObject *parent, int socketDescriptor,
                       WorkingCopy *workingCopy) :
    QThread(parent)
{
}

void SyncThread::run()
{
    //@TODO create read and write thread;
    //@TODO wait for read and write;
}
