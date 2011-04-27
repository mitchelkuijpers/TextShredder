#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QObject>
#include <QTimer>
#include "textshredderconnection.h"
#include "editlist.h"
#include "shadowcopy.h"
#include "workingcopy.h"

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
	void pushChanges();

private:
	void applyReceivedEditList(EditList &incomingEditList);

	TextShredderConnection * connection;
	WorkingCopy * workingCopy;
	ShadowCopy shadowCopy;
	EditList editList;
	QTimer timer;
};

#endif // SYNCTHREAD_H
