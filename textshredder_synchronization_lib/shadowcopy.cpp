#include "shadowcopy.h"
#include "editlist.h"


ShadowCopy::ShadowCopy(QObject *parent) :
		Patchable(parent), localVersion(0), remoteVersion(0)
{
	this->backupCopy = new BackupCopy(this, 0, "");
	incommingLog = new TextShredderLogging(this, "incommingShadowCopyLog.txt");
}

ShadowCopy::ShadowCopy(QObject *parent, QString content) :
		Patchable(parent), localVersion(0), remoteVersion(0)
{
	this->content = content;
	this->backupCopy = new BackupCopy(this, 0, content);
	incommingLog = new TextShredderLogging(this, "incommingShadowCopyLog.txt");
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

void ShadowCopy::applyEdits( QList<Edit> & edits )
{
	incommingLog->writeLog ("Apply edits");
	int count = 0;
	while(count < edits.size()){
		incommingLog->writeLog ("-- Apply Edit ");
		Edit e = edits.at(count);
		QString log("-- Edit localVersion =  ");
		log.append (QString::number (e.getLocalVersion ()));
		log.append (" remoteVersion = ");
		log.append (QString::number(remoteVersion));
		incommingLog->writeLog(log.toStdString ().c_str ());

		if(e.getLocalVersion() < remoteVersion){
			incommingLog->writeLog ("Should not apply edit");
			incommingLog->writeLog (((Patch)e.getPatches().at (0)).toString().toStdString ().c_str ());
			edits.removeAt(count);
		}
		else{
			incommingLog->writeLog ("Apply edit");
			incommingLog->writeLog (((Patch)e.getPatches().at (0)).toString().toStdString ().c_str ());
			this->applyPatches(e.getPatches());
			remoteVersion++;
			count++;
		}
	}
}



void ShadowCopy::processPatches( QList<Patch> &patches)
{
	this->applyPatches(patches);
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

void ShadowCopy::setLocalVersion(int version)
{
	localVersion = version;
}
