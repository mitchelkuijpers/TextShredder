#ifndef SHADOWCOPYTESTS_H
#define SHADOWCOPYTESTS_H

#include <QtCore/QString>
#include "../textshredder_core/libraries/synchronization/models/shadowcopy.h"
#include "autotest.h"


class ShadowCopyTests: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void revertTest();
	void backupTest();
	void applyEditsTestWithOnePatch();
	void applyEditsTestWithMultiplePatches();
	void applyEditsTestWhenAlreadyUpToDate();
};

DECLARE_TEST(ShadowCopyTests);

#endif // SHADOWCOPYTESTS_H
