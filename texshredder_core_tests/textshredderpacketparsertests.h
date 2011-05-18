#ifndef TEXTSHREDDERPACKETPARSERTESTS_H
#define TEXTSHREDDERPACKETPARSERTESTS_H

#include <QtCore>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include "../textshredder_core/libraries/network/textshredderpacketparser.h"
#include "autotest.h"
#include "../textshredder_core/libraries/network/models/textshredderheader.h"
#include "../textshredder_core/libraries/network/models/textshredderpacket.h"


class TextShredderPacketParserTests: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
                void testWrongPacket();
				void testPacket();
};

DECLARE_TEST(TextShredderPacketParserTests);

#endif // TEXTSHREDDERPACKETPARSERTESTS_H
