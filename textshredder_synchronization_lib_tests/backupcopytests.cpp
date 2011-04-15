#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/backupcopy.h"

class BackupCopyTests: public QObject
{
    Q_OBJECT

    public:
        BackupCopyTests();

    private Q_SLOTS:
        void createBackupCopyWithoutLocalVersionNumber();
        void createBackupCopyWithLocalVersionNumber();
};

BackupCopyTests::BackupCopyTests()
{
}

void BackupCopyTests::createBackupCopyWithDefaultLocalVersionNumber()
{
    TextShredderHeader * newTextShredder = new TextShredderHeader(this);

    QVERIFY2(newTextShredder != NULL, "Failed creating TSH object.");
}

void BackupCopyTests::createBackupCopyWithGivenLocalVersionNumber()
{
    QString * content;
    int localVersion = 5;

    BackupCopy * newBackupCopy= new BackupCopy(this, content, localVersion);

    QVERIFY2(newBackupCopy != NULL, "Failed creating BackupCopy object.");
    QVERIFY2(localVersion == newBackupCopy->getLocalVersion(),
             "Given localVersion is not equal to set localVersion in constructor");
    QVERIFY2(content == newBackupCopy->getContent(),
             "Given content is not equal to set content in constructor");
}

QTEST_APPLESS_MAIN(BackupCopyTests);

#include "backupcopytests.moc"
