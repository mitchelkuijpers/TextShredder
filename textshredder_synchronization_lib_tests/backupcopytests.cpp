#include "backupcopytests.h"
#include "../textshredder_synchronization_lib/backupcopy.h"

void BackupCopyTests::createBackupCopyWithDefaultLocalVersionNumber()
{
    BackupCopy * newBackupCopy= new BackupCopy(this);

    QVERIFY2(newBackupCopy != NULL, "Failed creating BackupCopy object.");
    QVERIFY2(newBackupCopy->getLocalVersion() == 0,
             "Given localVersion is not equal to 0");
}

void BackupCopyTests::createBackupCopyWithGivenLocalVersionNumber()
{
    int localVersion = 5;

    BackupCopy * newBackupCopy= new BackupCopy(this, localVersion);

    QVERIFY2(newBackupCopy != NULL, "Failed creating BackupCopy object.");
    QVERIFY2(localVersion == newBackupCopy->getLocalVersion(),
             "Given localVersion is not equal to set localVersion in constructor");
}
