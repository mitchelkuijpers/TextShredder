#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include <QThread>
#include "syncproperties.h"

class WriteThread : public QThread
{
    Q_OBJECT
public:
    explicit WriteThread(QObject *parent, SyncProperties *syncProperties);

signals:

public slots:

private:
    SyncProperties *syncProperties;
    void run();
};

#endif // WRITETHREAD_H
