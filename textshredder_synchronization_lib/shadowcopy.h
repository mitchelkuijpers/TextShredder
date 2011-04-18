#ifndef SHADOWCOPY_H
#define SHADOWCOPY_H

#include <QObject>
#include <QMutex>
#include "backupcopy.h"
#include "edit.h"
#include "patchable.h"


class ShadowCopy : public Patchable, QMutex
{
    Q_OBJECT

public:
	ShadowCopy( QObject *parent);
    int getLocalVersion();
	int getRemoteVersion();

    void revert();
    void backup();
	void applyEdits( QList<Edit> * );

	void processPatches( QList<Patch> * );

signals:

private:
    int localVersion;
    int remoteVersion;

    BackupCopy * backupCopy;
};

#endif // SHADOWCOPY_H
