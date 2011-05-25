#ifndef SHADOWCOPY_H
#define SHADOWCOPY_H

#include <QObject>
#include <QMutex>
#include "backupcopy.h"
#include "edit.h"
#include "patchable.h"
#include "../textshredder_core/libraries/logging/textshredderlogging.h"

class ShadowCopy : public Patchable, public QMutex
{
	Q_OBJECT

public:

	/**
	  * Constructor to make an ShadowCopy with a parent and a optional content.
	  * Will set the local and remote version to 0.
	  */
	ShadowCopy( QObject *parent, QString content = QString());


	/**
	  * Method to revert content to previous version. Content is parsed from the BackupCopy
	  * The local version is also reverted from the BackupCopy.
	  */
	void revert();

	/**
	  * Method to make a backup of your current version into the BackupCopy variable.
	  * It copies the content and the localVersion.
	  */
	void backup();

	/**
	  * Method to apply edits on the ShadowCopy content.
	  * All edits with lower local version then the objects <b><u>remote</u></b> version will not be processed.
	  *
	  * @param edits List of edits that need to be commited.
	  */
	void applyEdits( QList<Edit> & edits);

	/**
	  * Method to apply edits on the ShadowCopy content.
	  * All edits with lower local version then the objects <b><u>local</u></b> version will not be processed.
	  *
	  * @param edits List of edits that need to be applied.
	  */
	void applyLocalEdits( QList<Edit> & edits);

	/**
	  * Getter for the localVersion.
	  *
	  * @return The local version value.
	  */
	unsigned int getLocalVersion();

	/**
	  * Getter for the remoteVersion.
	  *
	  * @return The remote version value.
	  */
	unsigned int getRemoteVersion();

	/**
	  * Getter for the BackupCopy variable.
	  *
	  * @return The reference to the backupCopy variable.
	  */
	BackupCopy & getBackupCopy();

	/**
	  * Setter for the localversion
	  *
	  * @param The new local version.
	  */
	void setLocalVersion( int version );

private:
	unsigned int localVersion;
	unsigned int remoteVersion;

	BackupCopy backupCopy;
};

#endif // SHADOWCOPY_H
