#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>

#include "syncproperties.h"

class DownloadThread : public QThread
{
	Q_OBJECT
public:
	DownloadThread(QObject *, SyncProperties *, bool);

signals:
	void wrongPacketInDownloadThread(TextShredderPacket *);
	void sendTimeOut();
	void receiveTimeOut();
	void fileDownloadCompleted();
	void fileRequestFailed();

public slots:

private:
	void run();
	void makeFileRequest();
	void waitForFileRequest();

	SyncProperties *syncProperties;
	bool isServer;
};

#endif // DOWNLOADTHREAD_H
