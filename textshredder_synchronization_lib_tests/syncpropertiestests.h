#ifndef SYNCPROPERTIESTESTS_H
#define SYNCPROPERTIESTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/syncproperties.h"
#include "autotest.h"

class SyncPropertiesTests: public QObject
{
	Q_OBJECT

	public:
		SyncPropertiesTests();

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(SyncPropertiesTests)

#endif // SYNCPROPERTIESTESTS_H
