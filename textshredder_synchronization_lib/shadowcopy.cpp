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
	content = *(backupCopy->getContent());
}

void ShadowCopy::backup()
{
	backupCopy->setContent(this->content);
	backupCopy->setLocalVersion(this->localVersion);
}

void ShadowCopy::applyEdits( QList<Edit> & edits )
{
	QString logString("Shadow Copy::applyEdits");
	log(logString);
	int count = 0;
	while(count < edits.size()) {
		Edit e = edits.at(count);
		QString localVersionString("+ editBasedVersion: ");
		localVersionString.append(QString::number(e.getLocalVersion()));
		localVersionString.append (" - current known remote version: ");
		localVersionString.append (QString::number(remoteVersion));
		log(localVersionString);

		if(e.getLocalVersion() < remoteVersion) {
			QString removeEditMessage("Edit should not be processed");
			log(removeEditMessage);
			edits.removeAt(count);
		} else {
			QString applyEditMessage("Edit should be applied");
			log(applyEditMessage);
			this->applyPatches(e.getPatches());
			remoteVersion++;

			QString newRemoteVersionMessage("Shadow copy new remote version is: ");
			newRemoteVersionMessage.append (QString::number (remoteVersion));
			log(newRemoteVersionMessage);

			count++;
		}
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
