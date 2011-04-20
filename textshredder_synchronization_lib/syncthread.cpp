#include "syncthread.h"

SyncThread::SyncThread(QObject *parent, int socketDescriptor,
						WorkingCopy &workingCopy, bool server) :
	QThread(parent), syncProperties(this, socketDescriptor, &workingCopy),
	isServer(server), downloadThread(this, syncProperties, isServer),
	readThread(this, syncProperties), writeThread(this, syncProperties)
{
	connect(&downloadThread, SIGNAL(finished()), this, SLOT(downloadThreadFinished()));
	qDebug("SyncThread::SyncThread();");
}

void SyncThread::run()
{
	qDebug("SyncThread::run();");
	downloadThread.start();
	downloadThread.wait();

	readThread.start();
	writeThread.start();

	writeThread.wait();
	readThread.wait();
}

void SyncThread::downloadThreadFinished()
{
	qDebug("send downloadFinished signal");
	downloadFinished();
}
