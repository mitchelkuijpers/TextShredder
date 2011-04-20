#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QThread>
#include "syncproperties.h"
#include "writethread.h"
#include "readthread.h"
#include "textshreddersocket.h"
#include "downloadthread.h"

class SyncThread : public QThread
{
	Q_OBJECT

public:
	explicit SyncThread(QObject *, int , WorkingCopy &, bool);

signals:

public slots:

private:
	SyncProperties syncProperties;
	bool isServer;
	DownloadThread downloadThread;
	ReadThread readThread;
	WriteThread writeThread;

	/**
	  * Start DownloadThread, after finished start Read/WriteThread.
	  */
	void run();
};

#endif // SYNCTHREAD_H
