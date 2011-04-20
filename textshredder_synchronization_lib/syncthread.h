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
	explicit SyncThread(QObject *parent, int socketDescriptor,
						WorkingCopy *workingCopy);
	explicit SyncThread(QObject *parent, int socketDescriptor);

signals:

public slots:

private:
	SyncProperties *syncProperties;
	ReadThread *readThread;
	WriteThread *writeThread;
	bool isServer;

	/**
	  * Start DownloadThread, after finished start Read/WriteThread.
	  */
	void run();
};

#endif // SYNCTHREAD_H
