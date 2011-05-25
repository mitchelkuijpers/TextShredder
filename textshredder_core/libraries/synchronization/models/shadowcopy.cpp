#include "shadowcopy.h"
#include "editlist.h"

ShadowCopy::ShadowCopy(QObject *parent, QString content) :
		Patchable(parent, content), localVersion(0), remoteVersion(0),
		backupCopy(this, 0, content)
{
	//this->content = content;
	//this->backupCopy = new BackupCopy(this, 0, content);
}


void ShadowCopy::revert()
{
	content = *(backupCopy.getContent());
	localVersion = backupCopy.getLocalVersion();
}

void ShadowCopy::backup()
{
	backupCopy.setContent(this->content);
	backupCopy.setLocalVersion(this->localVersion);
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
			qDebug() << "++++++++++++++++++++++ Houston we have a problem -> ShadowCopy::applyEdits";
			count++;
		}
	}
}

void ShadowCopy::applyLocalEdits( QList<Edit> & edits )
{
	int count = 0;
	while(count < edits.size()) {
		Edit e = edits.at(count);

		if(e.getLocalVersion() == localVersion) {
			this->applyPatches(e.getPatches());
			localVersion++;
		} else {
			qDebug() << "++++++++++++++++++++++ Houston we have a another problem -> ShadowCopy::applyAckedEdits";
		}
		count++;
	}
}

unsigned int ShadowCopy::getRemoteVersion()
{
	return remoteVersion;
}

unsigned int ShadowCopy::getLocalVersion()
{
	return localVersion;
}

BackupCopy & ShadowCopy::getBackupCopy()
{
	return backupCopy;
}

void ShadowCopy::setLocalVersion(int version)
{
	localVersion = version;
}
