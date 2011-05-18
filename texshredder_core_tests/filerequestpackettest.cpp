#include "filerequestpackettest.h"
#include "../textshredder_core/libraries/network/models/filerequestpacket.h"
#include <QTest>

void  FileRequestPacketTest::testGetPort() {
	QString alias("test.txt");
	FileRequestPacket packet(this, 1337, alias);

	quint16 port = FileRequestPacket::getPort(packet);
	QVERIFY2(port == 1337, "port did not get out right");

	QString fileAlias = FileRequestPacket::getFileAlias(packet);
	QVERIFY2(fileAlias == QString("test.txt"), "filealias is not the same");
}
