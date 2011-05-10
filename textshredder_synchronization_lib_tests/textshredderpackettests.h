#ifndef TEXTSHREDDERPACKETTESTS_H
#define TEXTSHREDDERPACKETTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/textshredderpacket.h"
#include "autotest.h"
class TextShredderPacketTests: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void testCreatingBlankPacket();
	void testCreatingPacketWithHeaderAndContent();
	void testCreatingPacketWithTypeAndContent();
	void testCheckingOnEditPacket();
	void testCheckingOnFileRequestPacket();
	void testCheckingOnFileDataPacket();
	void testCheckingOnSetAliasPacket();
	void testAppendingData();
	void testNumberOfBytesNeeded();
};

DECLARE_TEST(TextShredderPacketTests);

#endif // TEXTSHREDDERPACKETTESTS_H
