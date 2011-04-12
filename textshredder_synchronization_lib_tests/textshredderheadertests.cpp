#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../textshredder_synchronization_lib/textshredderheader.h"

class TextShredderHeaderTests : public QObject
{
    Q_OBJECT

public:
    TextShredderHeaderTests();


private Q_SLOTS:
    void testEmptyHeaderCreation();
    void testHeaderCreationWihParameters();
};

TextShredderHeaderTests::TextShredderHeaderTests()
{
}

void TextShredderHeaderTests::testEmptyHeaderCreation()
{
    TextShredderHeader * newTextShredder = new TextShredderHeader();

    QVERIFY2(newTextShredder != NULL, "Failed creating TSH object.");
    QVERIFY2(newTextShredder->getProtocolVersion() == kProtocolVersion, "Failed protocol test");
    QVERIFY2(newTextShredder->getContentLength() == 0, "Failed content length: non-zero");
    QVERIFY2(newTextShredder->getPacketType() == 0, "Failed packet type: non-zero");
}

void TextShredderHeaderTests::testHeaderCreationWihParameters()
{
    char protocolVersion = 6;
    int contentLength = 900;
    char contentType = 2;

    TextShredderHeader * newTextShredder = new TextShredderHeader(protocolVersion, contentLength, contentType);

    QVERIFY2(newTextShredder != NULL, "Failed creating TSH object.");
    QVERIFY2(newTextShredder->getProtocolVersion() == protocolVersion, "Failed protocol test, value has to be " + protocolVersion);
    QVERIFY2(newTextShredder->getContentLength() == contentLength, "Failed content length, value has to be " + contentLength);
    QVERIFY2(newTextShredder->getPacketType() == contentType, "Failed packet type has to be " + contentType);
}

QTEST_APPLESS_MAIN(TextShredderHeaderTests);

#include "textshredderheadertests.moc"
