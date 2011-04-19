#ifndef BACKUPCOPY_H
#define BACKUPCOPY_H

#include <QObject>
#include "patchable.h"

class BackupCopy : public Patchable
{
    Q_OBJECT

public:
        BackupCopy( QObject *parent);
		BackupCopy( QObject *parent, unsigned int localVersion, QString content );
		unsigned int getLocalVersion();
		void setLocalVersion(unsigned int newLocalVersion);

signals:

public slots:

private:
	unsigned int localVersion;

};

#endif // BACKUPCOPY_H
