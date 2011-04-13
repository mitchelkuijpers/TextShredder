#ifndef SHADOWCOPY_H
#define SHADOWCOPY_H

#include <QObject>
#include <QMutex>
#include "backupcopy.h"

class ShadowCopy : public QObject
{
    Q_OBJECT
public:
    ShadowCopy(QObject *parent);

signals:

public slots:

private:
    int localVersion;
    int remoteVersion;

    QMutex * mutex;
    QString * content;
    BackupCopy * backupCopy;
};

#endif // SHADOWCOPY_H
