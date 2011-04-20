#include "readthread.h"

ReadThread::ReadThread(QObject *parent, SyncProperties &properties) :
	QThread(parent), syncProperties(&properties)
{
}

void ReadThread::run()
{
	TextShredderSocket * socket = syncProperties->getSocket();
	connect(this, SIGNAL(newDataReady()), syncProperties, SLOT(processChanges()));

	while(true) {
		if(socket->waitForReadyRead(30000)){
			emit newDataReady();
		}
	}
}
