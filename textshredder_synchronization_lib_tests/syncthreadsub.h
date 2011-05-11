#ifndef SYNCTHREADSUB_H
#define SYNCTHREADSUB_H

#include <QObject>
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../textshredder_gui/textshredderlogging.h"

#include "../textshredder_synchronization_lib/editlist.h"

class SyncThreadSub : public SyncThread
{
    Q_OBJECT
public:

    SyncThreadSub(QObject *parent, TextShredderConnection & newConnection, WorkingCopy & newWorkingCopy);


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
