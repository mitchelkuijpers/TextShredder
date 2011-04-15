#include "backupcopy.h"

BackupCopy::BackupCopy( QObject *parent, QString & content ) :
    QObject(parent), content(content), localVersion(0)
{
}

BackupCopy::BackupCopy( QObject *parent, QString & content, int localVersion ) :
    QObject(parent), content(content), localVersion(localVersion)
{
}

int BackupCopy::getLocalVersion()
{
    return localVersion;
}

QString * BackupCopy::getContent()
{
    return content;
}
