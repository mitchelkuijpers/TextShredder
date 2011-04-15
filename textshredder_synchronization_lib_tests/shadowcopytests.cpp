#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/shadowcopy.h"

class ShadowCopyTests: public QObject
{
    Q_OBJECT

    public:
        ShadowCopyTests();

    private Q_SLOTS:
        void testHello();
};

ShadowCopyTests::ShadowCopyTests()
{
}

void ShadowCopyTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(ShadowCopyTests);

#include "shadowcopytests.moc"

