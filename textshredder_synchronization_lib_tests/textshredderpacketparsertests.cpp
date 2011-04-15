#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/textshredderpacketparser.h"

class TextShredderPacketParserTests: public QObject
{
    Q_OBJECT

    public:
        TextShredderPacketParserTests();

    private Q_SLOTS:
        void testHello();
};

TextShredderPacketParserTests::TextShredderPacketParserTests()
{
}

void TextShredderPacketParserTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

QTEST_APPLESS_MAIN(TextShredderPacketParserTests);

#include "textshredderpacketparsertests.moc"


