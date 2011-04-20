#ifndef READTHREAD_H
#define READTHREAD_H

#include <QThread>
#include "syncproperties.h"

class ReadThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadThread(QObject *parent, SyncProperties *syncProperties);

signals:
	void newDataReady();


public slots:

private:
    SyncProperties *syncProperties;
	/**
	  * Send signal to syncproperties when there are new changes waiting.
	  */
    void run();
};

#endif // READTHREAD_H
