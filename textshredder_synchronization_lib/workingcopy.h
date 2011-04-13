#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

#include <QObject>
#include <QMutex>

class WorkingCopy : public QObject
{
    Q_OBJECT
public:
    WorkingCopy(QObject *parent = 0);

signals:

public slots:

private:
    QString *content;
    QMutex *mutex;

};

#endif // WORKINGCOPY_H
