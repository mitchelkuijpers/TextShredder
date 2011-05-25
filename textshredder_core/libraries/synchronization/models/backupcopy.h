#ifndef BACKUPCOPY_H
#define BACKUPCOPY_H

#include <QObject>
#include "patchable.h"

class BackupCopy : public Patchable
{
    Q_OBJECT

public:
	/**
	 * Constructor. Passes the parent to the Patchable class
	 * Sets the localversion variable to zero.
	 *
	 * @param parent The parent of the object.
	 */
	BackupCopy( QObject *parent);

	/**
	 * Constructor. Passes the parent to the Patchable class
	 * Sets the localversion to the localVersion variable.
	 * Set content to the content param
	 *
	 * @param parent The parent of the object.
	 * @param localVersion The localversion of the backupcopy
	 * @param content The content of the backupcopy
	 */
	BackupCopy( QObject *parent, unsigned int localVersion, QString content );

	/**
	  * Method returns the local version of the Backup object
	  *
	  * @return The local version of the Backup object.
	  */
	unsigned int getLocalVersion();

	/**
	  * Method will set the local version of the Backup object
	  *
	  * @param The new local version of the Backup object.
	  */
	void setLocalVersion(unsigned int newLocalVersion);

private:
	/**
	  * The local version of the BackupCopy object.
	  */
	unsigned int localVersion;

};

#endif // BACKUPCOPY_H
