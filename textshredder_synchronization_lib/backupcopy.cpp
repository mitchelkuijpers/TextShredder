#include "backupcopy.h"

BackupCopy::BackupCopy( QObject *parent, QString & content ) :
	QObject(parent), localVersion(0), content(content)
{
}

BackupCopy::BackupCopy( QObject *parent, QString & content, int localVersion ) :
	QObject(parent),  localVersion(localVersion), content(content)
{
}

int BackupCopy::getLocalVersion()
{
    return localVersion;
}

QString BackupCopy::getContent()
{
    return content;
}
