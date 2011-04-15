#ifndef TEXTSHREDDERHEADERTESTS_H
#define TEXTSHREDDERHEADERTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/textshredderheader.h"
#include "autotest.h"

class TextShredderHeaderTests : public QObject
{
	Q_OBJECT

public:
	TextShredderHeaderTests();


private Q_SLOTS:
	void testEmptyHeaderCreation();
	void testHeaderCreationWihParameters();

	void testHeaderWriteToQByteArray();
	void testHeaderCreationFromQByteArray();

	void testHeaderSerializationAndDeserialization();
};

DECLARE_TEST(TextShredderHeaderTests);

#endif // TEXTSHREDDERHEADERTESTS_H
