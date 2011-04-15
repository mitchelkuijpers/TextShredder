#ifndef EDITLISTTESTS_H
#define EDITLISTTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/editlist.h"
#include "autotest.h"

class EditListTests: public QObject
{
	Q_OBJECT

	public:
		EditListTests();

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(EditListTests)

#endif // EDITLISTTESTS_H
