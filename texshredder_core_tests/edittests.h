#ifndef EDITTESTS_H
#define EDITTESTS_H

#include <QtCore/QString>
#include "../textshredder_core/libraries/synchronization/models/edit.h"
#include "autotest.h"

class EditTests: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
                    void testCreateEmptyConstructor();
                    void testCreateConstructorWithParameters();
};

DECLARE_TEST(EditTests);

#endif // EDITTESTS_H
