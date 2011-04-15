#ifndef TEXTSHREDDERPACKETPARSERTESTS_H
#define TEXTSHREDDERPACKETPARSERTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/textshredderpacketparser.h"
#import "autotest.h"

class TextShredderPacketParserTests: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(TextShredderPacketParserTests);

#endif // TEXTSHREDDERPACKETPARSERTESTS_H
