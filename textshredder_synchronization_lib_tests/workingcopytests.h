#ifndef WORKINGCOPYTESTS_H
#define WORKINGCOPYTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "autotest.h"

class WorkingCopyTests: public QObject
{
	Q_OBJECT

	public:
		WorkingCopyTests();

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(WorkingCopyTests);


#endif // WORKINGCOPYTESTS_H
