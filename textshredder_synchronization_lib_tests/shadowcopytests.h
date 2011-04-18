#ifndef SHADOWCOPYTESTS_H
#define SHADOWCOPYTESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/shadowcopy.h"
#include "autotest.h"


class ShadowCopyTests: public QObject
{
	Q_OBJECT


	private Q_SLOTS:
				void revertTest();
				void backupTest();
				void applyEditsTest();
				void processPatchesTest();




};

DECLARE_TEST(ShadowCopyTests);

#endif // SHADOWCOPYTESTS_H
