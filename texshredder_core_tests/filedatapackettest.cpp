#include "filedatapackettest.h"
#include "../textshredder_core/libraries/network/models/filedatapacket.h"
#include <QTest>

void FileDataPacketTest::testGetRemoteFileHandle()
{
	QByteArray string("Dont you dare to get stuff of of my content!");
	quint16 filehandle = 34;
	FileDataPacket * packet = new FileDataPacket(NULL, string, filehandle);

	QVERIFY2(FileDataPacket::getConnectionHandle(*packet) == 34, "getConnection handle fails");
}

void FileDataPacketTest::testGetFileDataContent()
{
	QByteArray string("1337 Dont you dare to get stuff of of my content!");
	quint16 filehandle = 45;
	FileDataPacket * packet = new FileDataPacket(NULL, string, filehandle);

	QVERIFY2(FileDataPacket::getFileDataContent(*packet) == string, "getContent handle fails");
}
