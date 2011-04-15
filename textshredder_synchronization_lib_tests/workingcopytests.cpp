#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/workingcopy.h"

class WorkingCopyTests: public QObject
{
    Q_OBJECT

    public:
        WorkingCopyTests();

    private Q_SLOTS:
        void testHello();
};

WorkingCopyTests::WorkingCopyTests()
{
}

void WorkingCopyTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(WorkingCopyTests);

#include "workingcopytests.moc"

