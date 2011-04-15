#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

#include <QObject>
#include <QMutex>

class WorkingCopy : public QObject
{
    Q_OBJECT
public:
    WorkingCopy(QObject *parent);

signals:

public slots:

private:
    QMutex *mutex;

};

#endif // WORKINGCOPY_H
