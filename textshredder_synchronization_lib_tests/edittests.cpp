#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/edit.h"

class EditTests: public QObject
{
    Q_OBJECT

    public:
        EditTests();

    private Q_SLOTS:
        void testHello();
};

EditTests::EditTests()
{
}

void EditTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(EditTests);

#include "edittests.moc"

