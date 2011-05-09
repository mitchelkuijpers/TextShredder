#include "backupcopy.h"

BackupCopy::BackupCopy( QObject *parent ) :
		Patchable(parent), localVersion(0)
{
}

BackupCopy::BackupCopy( QObject *parent, unsigned int localVersion, QString content ) :
		Patchable(parent),  localVersion(localVersion)
{
	this->content = content;
}

unsigned int BackupCopy::getLocalVersion()
{
    return localVersion;
}

void BackupCopy::setLocalVersion(unsigned int newLocalVersion)
{
	this->localVersion = newLocalVersion;
}
