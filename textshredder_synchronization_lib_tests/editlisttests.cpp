#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/editlist.h"

class EditListTests: public QObject
{
    Q_OBJECT

    public:
        EditListTests();

    private Q_SLOTS:
        void testHello();
};

EditListTests::EditListTests()
    {

    }

void EditListTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(EditListTests);

#include "editlisttests.moc"
