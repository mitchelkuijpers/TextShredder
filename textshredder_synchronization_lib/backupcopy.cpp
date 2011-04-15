#include "backupcopy.h"

BackupCopy::BackupCopy( QObject *parent ) :
        QObject(parent), localVersion(0)
{
}

BackupCopy::BackupCopy( QObject *parent, int localVersion ) :
        QObject(parent),  localVersion(localVersion)
{
}

int BackupCopy::getLocalVersion()
{
    return localVersion;
}
