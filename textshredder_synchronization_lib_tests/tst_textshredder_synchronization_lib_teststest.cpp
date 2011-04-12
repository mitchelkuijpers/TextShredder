#include <QtCore/QString>
#include <QtTest/QtTest>

class Textshredder_synchronization_lib_testsTest : public QObject
{
    Q_OBJECT

public:
    Textshredder_synchronization_lib_testsTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

Textshredder_synchronization_lib_testsTest::Textshredder_synchronization_lib_testsTest()
{
}

void Textshredder_synchronization_lib_testsTest::initTestCase()
{
}

void Textshredder_synchronization_lib_testsTest::cleanupTestCase()
{
}

void Textshredder_synchronization_lib_testsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Textshredder_synchronization_lib_testsTest);

#include "tst_textshredder_synchronization_lib_teststest.moc"
