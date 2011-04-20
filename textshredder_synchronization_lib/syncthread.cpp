#include "syncthread.h"

SyncThread::SyncThread(QObject *parent, int socketDescriptor,
                       WorkingCopy *workingCopy) :
    QThread(parent)
{
	syncProperties = new SyncProperties(this, socketDescriptor, workingCopy);
	isServer = true;
}

SyncThread::SyncThread(QObject *parent, int socketDescriptor) :
	QThread(parent)
{
	WorkingCopy copy(this);
	syncProperties = new SyncProperties(this, socketDescriptor, &copy);
	isServer = false;
}

void SyncThread::run()
{
	DownloadThread downloadThread(this, syncProperties, isServer);
	downloadThread.start();
	downloadThread.wait();

	ReadThread readThread(this, syncProperties);
	readThread.start();
	WriteThread writeThread(this, syncProperties);
	writeThread.start();

	writeThread.wait();
	readThread.wait();
}
