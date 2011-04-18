#ifndef TEXTSHREDDERPACKETPARSERTESTS_H
#define TEXTSHREDDERPACKETPARSERTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/textshredderpacketparser.h"
#include "autotest.h"
#include "../textshredder_synchronization_lib/textshredderheader.h"
#include "../textshredder_synchronization_lib/textshredderpacket.h"


class TextShredderPacketParserTests: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
                void testWrongPacket();
};

DECLARE_TEST(TextShredderPacketParserTests);

#endif // TEXTSHREDDERPACKETPARSERTESTS_H
