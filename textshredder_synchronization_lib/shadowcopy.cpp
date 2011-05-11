#include "shadowcopy.h"
#include "editlist.h"


ShadowCopy::ShadowCopy(QObject *parent) :
		Patchable(parent), localVersion(0), remoteVersion(0), logging(NULL)
{
	this->backupCopy = new BackupCopy(this, 0, "");
}

ShadowCopy::ShadowCopy(QObject *parent, QString content) :
		Patchable(parent), localVersion(0), remoteVersion(0), logging(NULL)
{
	this->content = content;
	this->backupCopy = new BackupCopy(this, 0, content);
}


void ShadowCopy::revert()
{
	QString revertMessage("Will revert Shadow Copy: ");
	revertMessage.append(QString::number(localVersion));
	revertMessage.append(" to ");
	content = *(backupCopy->getContent());
	localVersion = backupCopy->getLocalVersion();
	revertMessage.append(QString::number(localVersion));
	log(revertMessage);
}

void ShadowCopy::backup()
{
	backupCopy->setContent(this->content);
	backupCopy->setLocalVersion(this->localVersion);
}

void ShadowCopy::applyEdits( QList<Edit> & edits )
{
	int count = 0;
	while(count < edits.size()) {
		Edit e = edits.at(count);

		if(e.getLocalVersion() < remoteVersion) {
			edits.removeAt(count);
		} else if (e.getLocalVersion() ==  remoteVersion){
			this->applyPatches(e.getPatches());
			remoteVersion++;
			count++;
		} else {
			QString logMessage("++++++++++++++++++++++ Houston we have a problem -> ShadowCopy::applyEdits");
			log(logMessage);
			count++;
		}
	}
}

void ShadowCopy::applyLocalEdits( QList<Edit> & edits )
{
	QString logm("Current local version is -> ");
	logm.append(QString::number(this->localVersion));
	log(logm);
	int count = 0;
	while(count < edits.size()) {
		Edit e = edits.at(count);

		if(e.getLocalVersion() == localVersion) {
			this->applyPatches(e.getPatches());
			QString logMessage("Increase Local Version");
			log(logMessage);
			localVersion++;
		} else {
			QString logMessage("++++++++++++++++++++++ Houston we have a another problem -> ShadowCopy::applyAckedEdits");
			log(logMessage);
		}
		count++;
	}
}

void ShadowCopy::processPatches( QList<Patch> &patches)
{
	this->applyPatches(patches);
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

void ShadowCopy::setLogging(TextShredderLogging *log)
{
	this->logging = log;
}

void ShadowCopy::log(QString &logString)
{
	if(logging != NULL) {
		logging->writeLog (logString, DEBUG);
	}
}
