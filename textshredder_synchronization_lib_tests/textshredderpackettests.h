#ifndef TEXTSHREDDERPACKETTESTS_H
#define TEXTSHREDDERPACKETTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/textshredderpacket.h"
#include "autotest.h"
class TextShredderPacketTests: public QObject
{
	Q_OBJECT

	public:
		TextShredderPacketTests();

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(TextShredderPacketTests);

#endif // TEXTSHREDDERPACKETTESTS_H
