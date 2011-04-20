#include "writethread.h"

WriteThread::WriteThread(QObject *parent, SyncProperties *syncProperties) :
    QThread(parent), syncProperties(syncProperties)
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

