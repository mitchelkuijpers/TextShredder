#ifndef SHADOWCOPY_H
#define SHADOWCOPY_H

#include <QObject>
#include <QMutex>
#include "backupcopy.h"

class ShadowCopy : public QObject
{
    Q_OBJECT

public:
    ShadowCopy( QObject *parent, int );
    int getLocalVersion();
    void revert();
    void backup();
    //void applyEdits( QList<Edit> * );
    int getRemoteVersion();
    //void processPatches( QList<Patch> * );

signals:

private:
    int localVersion;
    int remoteVersion;

    QMutex * mutex;
    BackupCopy * backupCopy;
};

#endif // SHADOWCOPY_H
