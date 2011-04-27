#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QObject>
#include <QTimer>
#include "syncproperties.h"
#include "textshreddersocket.h"
#include "downloadthread.h"
#include "textshredderconnection.h"

#define WRITETHREAD_INTERVAL 2000

class SyncThread : public QObject
{
	Q_OBJECT

public:
	SyncThread(QObject *, TextShredderConnection &, WorkingCopy &);

signals:

public slots:
	void processChanges(TextShredderPacket&);
	void stop();

private:
	void pushChanges();
	void applyReceivedEditList(EditList &incomingEditList);

	TextShredderConnection * connection;
	WorkingCopy * workingCopy;
	ShadowCopy shadowCopy;
	EditList editList;
	QTimer timer;
};

#endif // SYNCTHREAD_H
