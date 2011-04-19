#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

#include <QObject>
#include <QMutex>

class WorkingCopy : public QObject, QMutex
{
    Q_OBJECT
public:
    WorkingCopy(QObject *parent);

signals:

public slots:

private:


};

#endif // WORKINGCOPY_H
