#ifndef TEXTSHREDDERHEADERTESTS_H
#define TEXTSHREDDERHEADERTESTS_H

#include <QtCore/QString>
#include "autotest.h"

class TextShredderHeaderTests : public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void testEmptyHeaderCreation();
	void testHeaderCreationWihParameters();

	void testHeaderWriteToQByteArray();
	void testHeaderCreationFromQByteArray();

	void testHeaderSerializationAndDeserialization();
};

DECLARE_TEST(TextShredderHeaderTests);

#endif // TEXTSHREDDERHEADERTESTS_H
