#ifndef SYNCTHREADSUB_H
#define SYNCTHREADSUB_H

#include "syncTh"
#include <QObject>

class SyncThreadSub : public QObject
{
    Q_OBJECT
public:
    explicit SyncThreadSub(QObject *parent = 0);

signals:

public slots:

};

#endif // SYNCTHREADSUB_H
