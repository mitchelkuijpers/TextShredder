#ifndef TEXTSHREDDERSOCKETTESTS_H
#define TEXTSHREDDERSOCKETTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/textshreddersocket.h"
#include "autotest.h"

class TextShredderSocketTests: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
		void testHello();
};

DECLARE_TEST(TextShredderSocketTests);

#endif // TEXTSHREDDERSOCKETTESTS_H
