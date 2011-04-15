#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/syncproperties.h"

class SyncPropertiesTests: public QObject
{
    Q_OBJECT

    public:
        SyncPropertiesTests();

    private Q_SLOTS:
        void testHello();
};

SyncPropertiesTests::SyncPropertiesTests()
{
}

void SyncPropertiesTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(SyncPropertiesTests);

#include "syncpropertiestests.moc"

