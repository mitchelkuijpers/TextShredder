#include "backupcopytests.h"
#include "../textshredder_synchronization_lib/backupcopy.h"

void BackupCopyTests::createBackupCopyWithDefaultLocalVersionNumber()
{
}

void BackupCopyTests::createBackupCopyWithGivenLocalVersionNumber()
{
	QString content;
    int localVersion = 5;

	BackupCopy * newBackupCopy= new BackupCopy(this, content, localVersion);

    QVERIFY2(newBackupCopy != NULL, "Failed creating BackupCopy object.");
    QVERIFY2(localVersion == newBackupCopy->getLocalVersion(),
             "Given localVersion is not equal to set localVersion in constructor");
	QVERIFY2(content == newBackupCopy->getContent(),
             "Given content is not equal to set content in constructor");
}
