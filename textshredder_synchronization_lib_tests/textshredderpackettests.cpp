#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/textshredderpacket.h"

class TextShredderPacketTests: public QObject
{
    Q_OBJECT

    public:
        TextShredderPacketTests();

    private Q_SLOTS:
        void testHello();
};

TextShredderPacketTests::TextShredderPacketTests()
{
}

void TextShredderPacketTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(TextShredderPacketTests);

#include "textshredderpackettests.moc"


