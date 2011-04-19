#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

#include <QObject>
#include <QMutex>
#include "patchable.h"

class WorkingCopy : public Patchable, public QMutex
{
    Q_OBJECT
public:
    WorkingCopy(QObject *parent);

signals:

public slots:

private:


};

#endif // WORKINGCOPY_H
