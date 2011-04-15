#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/textshreddersocket.h"

class TextShredderSocketTests: public QObject
{
    Q_OBJECT

    public:
        TextShredderSocketTests();

    private Q_SLOTS:
        void testHello();
};

TextShredderSocketTests::TextShredderSocketTests()
{
}

void TextShredderSocketTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(TextShredderSocketTests);

#include "textshreddersockettests.moc"


