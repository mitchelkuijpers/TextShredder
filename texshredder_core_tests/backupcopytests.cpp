#include "backupcopytests.h"
#include "../textshredder_core/libraries/synchronization/models/backupcopy.h"

void BackupCopyTests::createBackupCopyWithDefaultLocalVersionNumber()
{
    BackupCopy * newBackupCopy= new BackupCopy(this);

    QVERIFY2(newBackupCopy != NULL, "Failed creating BackupCopy object.");
    QVERIFY2(newBackupCopy->getLocalVersion() == 0,
             "Given localVersion is not equal to default 0");
}

void BackupCopyTests::createBackupCopyWithGivenLocalVersionNumber()
{
	unsigned int localVersion = 5;
	QString testContent = "HALALLAFLAJFLAJL AAKLAFSLKDFJIFELJ asdfadsf";

	BackupCopy * newBackupCopy= new BackupCopy(this, localVersion, testContent);

    QVERIFY2(newBackupCopy != NULL, "Failed creating BackupCopy object.");
	QVERIFY2(localVersion == newBackupCopy->getLocalVersion(),
             "Given localVersion is not equal to set localVersion in constructor");
}
