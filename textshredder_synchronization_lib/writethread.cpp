#include "writethread.h"

WriteThread::WriteThread(QObject *parent, SyncProperties &properties) :
	QThread(parent), syncProperties(&properties)
{
}

void WriteThread::run()
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), syncProperties, SLOT(pushChanges()));
	timer->start(WRITETHREAD_INTERVAL);
	while(timer->isActive()) {
		//keep the thread open.
	}
}

