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
		 * @param Qobject parent.
		 */
        BackupCopy( QObject *parent);

		/**
		 * Constructor. Passes the parent to the Patchable class
		 * Sets the localversion to the localVersion variable.
		 * Set content to the content param
		 *
		 * @param Qobject parent.
		 * @param localVersion The localversion of the backupcopy
		 * @param content, the content of the backupcopy
		 */
		BackupCopy( QObject *parent, unsigned int localVersion, QString content );
		unsigned int getLocalVersion();
		void setLocalVersion(unsigned int newLocalVersion);

signals:

public slots:

private:
	unsigned int localVersion;

};

#endif // BACKUPCOPY_H
