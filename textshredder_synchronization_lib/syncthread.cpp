#include "syncthread.h"

SyncThread::SyncThread(QObject *parent, int socketDescriptor,
						WorkingCopy &workingCopy, bool server) :
	QThread(parent), syncProperties(this, socketDescriptor, &workingCopy), isServer(server)
{
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
