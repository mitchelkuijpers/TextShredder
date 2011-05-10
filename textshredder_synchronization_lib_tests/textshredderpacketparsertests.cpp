#include "textshredderpacketparsertests.h"
#include "../textshredder_synchronization_lib/textshredderpacket.h"
#include <QString>
#include <QDebug>

void TextShredderPacketParserTests::testWrongPacket()
{

}

void TextShredderPacketParserTests::testPacket()
{
	//Create QBytearray to send to the function

	QByteArray tempContent = "This is testcontent";
	QByteArray tempContent2 = "This is awesome content";
	unsigned char type = (unsigned char)kPacketTypeEdits;

	TextShredderPacket packet(this, type, tempContent);
	TextShredderPacket packet2(this, type, tempContent2);

	QByteArray raw;
	packet.getHeader().appendToQByteArray(raw);
	raw.append(packet.getContent());
	packet2.getHeader().appendToQByteArray(raw);
	raw.append(packet2.getContent());

	TextShredderPacketParser parser;

	int i = 0;

	for(i = 0; raw.size(); i++) {
		QByteArray temp = raw.mid(i, 1);
		parser.handleData(temp);
	}
	QVERIFY2(parser.hasMorePackets() == true, "The packet has more packets after handling it.");

	QVERIFY2((*parser.nextPacket()) == packet, "The first packet is NOT packet");

	QVERIFY2((*parser.nextPacket()) == packet2, "The next packet to get handled is NOT packet2");
}
