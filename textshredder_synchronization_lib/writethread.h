#ifndef WRITETHREAD_H
#define WRITETHREAD_H
#define WRITETHREAD_INTERVAL 2000

#include <QThread>
#include "syncproperties.h"
#include <QTimer>

class WriteThread : public QThread
{
    Q_OBJECT

public:
    explicit WriteThread(QObject *parent, SyncProperties *syncProperties);

private:
    SyncProperties *syncProperties;
	/**
	  * Push changes every ms defined by WRITETHREAD_INTERVAL
	  */
    void run();
};

#endif // WRITETHREAD_H
