#ifndef SYNCTHREADSUB_H
#define SYNCTHREADSUB_H

#include <QObject>
#include "../textshredder_core/libraries/synchronization/syncthread.h"
#include "../textshredder_core/libraries/logging/textshredderlogging.h"

#include "../textshredder_core/libraries/synchronization/models/editlist.h"

class SyncThreadSub : public SyncThread
{
    Q_OBJECT
public:

	SyncThreadSub(QObject *parent, QSharedPointer<WorkingCopy> newWorkingCopy);


    using SyncThread::processChanges;
    void processChanges(QByteArray &content);

    using SyncThread::pushChanges;
    void pushChanges();

    using SyncThread::writePacketOfEditList;
    void writePacketOfEditList();

	using SyncThread::startSync;
	void startSync();

	EditList * getEditList();
	WorkingCopy * getWorkingCopy();
	ShadowCopy * getShadowCopy();
signals:

public slots:

private:
    TextShredderLogging *logfile;

};


#endif // SYNCTHREADSUB_H
