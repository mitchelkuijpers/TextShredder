#ifndef SHADOWCOPY_H
#define SHADOWCOPY_H

#include <QObject>
#include <QMutex>
#include "backupcopy.h"

class ShadowCopy : public QObject
{
    Q_OBJECT

public:
	ShadowCopy( QObject *parent, QString *, int );
    void lock();
    void unlock();
    int getLocalVersion();
    void revert();
    void backup();
//    void applyEdits( QList<Edit> * );
    int getRemoteVersion();
    QString * getContent();
//    void processPatches( QList<Patch> * );

signals:

private:
    int localVersion;
    int remoteVersion;

    QMutex * mutex;
    QString * content;
    BackupCopy * backupCopy;
};

#endif // SHADOWCOPY_H
