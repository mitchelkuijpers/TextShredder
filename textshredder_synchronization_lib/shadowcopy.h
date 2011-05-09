#ifndef SHADOWCOPY_H
#define SHADOWCOPY_H

#include <QObject>
#include <QMutex>
#include "backupcopy.h"
#include "edit.h"
#include "patchable.h"
#include "../textshredder_gui/textshredderlogging.h"

class ShadowCopy : public Patchable, public QMutex
{
    Q_OBJECT

public:
	ShadowCopy( QObject *parent);
	ShadowCopy( QObject *parent, QString content);

	/*getters*/
	unsigned int getLocalVersion();
	unsigned int getRemoteVersion();
	BackupCopy *getBackupCopy();

	/**
	  *  Function to revert content to previous version
	  */
	void revert();

	/**
	  *  Fucntion to make a backup of your current version
	  */
	void backup();

	/**
	  * Fucntion to apply edits if not done yet to the Shadow Copy
	  * @param List of edits that need to be commited
	  */
	void applyEdits( QList<Edit> & edits);

	/**
	  * Function to apply the changes you have made in your workingcopy
	  * @param List of patches from changes you made
	  */
	void processPatches( QList<Patch> & patches);

	void setLocalVersion(int version);
signals:

private:
	unsigned int localVersion;
	unsigned int remoteVersion;

	BackupCopy * backupCopy;
	TextShredderLogging *incommingLog;
};

#endif // SHADOWCOPY_H
