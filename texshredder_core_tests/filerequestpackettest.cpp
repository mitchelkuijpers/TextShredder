#include "filerequestpackettest.h"
#include "../textshredder_core/libraries/network/models/filerequestpacket.h"
#include <QTest>

void  FileRequestPacketTest::testGetPort() {
	QString identifier("{1234-5678-9012-3456-7890}");
	FileRequestPacket packet(this, 1337, identifier);

	quint16 sourceHandle = FileRequestPacket::getSourceHandle(packet);
	QVERIFY2(sourceHandle == 1337, "port did not get out right");

	QString fileIdentifier= FileRequestPacket::getFileIdentifier(packet);
	QVERIFY2(identifier == fileIdentifier, "fileIdentifier is not the same");
}
