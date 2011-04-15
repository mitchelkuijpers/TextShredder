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

public slots:

private:
    SyncProperties *syncProperties;
    void run();
};

#endif // READTHREAD_H
