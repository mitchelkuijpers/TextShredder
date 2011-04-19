#ifndef WORKINGCOPYTESTS_H
#define WORKINGCOPYTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "autotest.h"

class WorkingCopyTests: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
		void testGetPatchableContent();
};

DECLARE_TEST(WorkingCopyTests);


#endif // WORKINGCOPYTESTS_H
