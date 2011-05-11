#ifndef SYNCTHREADSUB_H
#define SYNCTHREADSUB_H

#include <QObject>
#include "../textshredder_synchronization_lib/syncthread.h"
#include "../textshredder_gui/textshredderlogging.h"

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


signals:

public slots:

private:
    TextShredderLogging *logfile;

};


#endif // SYNCTHREADSUB_H
