#include "shadowcopy.h"
#include "editlist.h"


ShadowCopy::ShadowCopy(QObject *parent) :
		Patchable(parent), localVersion(0), remoteVersion(0)
{
	this->backupCopy = new BackupCopy(this, 0, "");
}

ShadowCopy::ShadowCopy(QObject *parent, QString content) :
		Patchable(parent), localVersion(0), remoteVersion(0)
{
	this->content = content;
	this->backupCopy = new BackupCopy(this, 0, content);
}


void ShadowCopy::revert()
{
	content = *(backupCopy->getContent());
	this->localVersion = backupCopy->getLocalVersion();

}

void ShadowCopy::backup()
{
	backupCopy->setContent(this->content);
	backupCopy->setLocalVersion(this->localVersion);

}

void ShadowCopy::applyEdits( QList<Edit> * edits )
{

	int count = 0;
	while(count < edits->size()){
		Edit e = edits->at(count);
		if(e.getLocalVersion() < remoteVersion){
			edits->removeAt(count);
			//qDebug("already patched");
		}
		else{
			this->applyPatches(e.getPatches());
			remoteVersion++;
			count++;
			//qDebug("patched");
		}
	}



}



void ShadowCopy::processPatches( QList<Patch> * patches)
{
	this->applyPatches(*patches);
	localVersion++;

}

unsigned int ShadowCopy::getRemoteVersion()
{
	return remoteVersion;
}

unsigned int ShadowCopy::getLocalVersion()
{
	return localVersion;
}

BackupCopy * ShadowCopy::getBackupCopy()
{
	return backupCopy;
}
