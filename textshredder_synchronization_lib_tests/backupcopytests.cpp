#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/backupcopy.h"

class BackupCopyTests: public QObject
{
    Q_OBJECT

    public:
        BackupCopyTests();

    private Q_SLOTS:
        void testHello();
};

BackupCopyTests::BackupCopyTests()
{
}

void BackupCopyTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(BackupCopyTests);

#include "backupcopytests.moc"
