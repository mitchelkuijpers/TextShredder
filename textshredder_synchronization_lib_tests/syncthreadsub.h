#ifndef SYNCTHREADSUB_H
#define SYNCTHREADSUB_H

#include <QObject>
#include "../textshredder_synchronization_lib/syncthread.h"

class SyncThreadSub : public QObject
{
    Q_OBJECT
public:
    SyncThreadSub(QObject *parent = 0);


signals:

public slots:

};

#endif // SYNCTHREADSUB_H
