#ifndef EDITTESTS_H
#define EDITTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/edit.h"
#include "autotest.h"

class EditTests: public QObject
{
	Q_OBJECT

	public:
		EditTests();

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(EditTests);

#endif // EDITTESTS_H
