#ifndef SYNCTHREADTESTS_H
#define SYNCTHREADTESTS_H

#include <QtCore/QString>
#include "autotest.h"
#include "syncthreadsub.h"

class SyncThreadTests : public QObject
{
    Q_OBJECT

public:
	void setupVariables();

private Q_SLOTS:
	void simpleSyncTest();
    void pushChangesTest();
    void writePacketOfEditListTest();

private:
	SyncThreadSub *leftSync;
	SyncThreadSub *rightSync;

	WorkingCopy *leftWorkingCopy;
	WorkingCopy *rightWorkingCopy;

	ShadowCopy *leftShadowCopy;
	ShadowCopy *rightShadowCopy;

	EditList *leftEditList;
	EditList *rightEditList;
};

DECLARE_TEST(SyncThreadTests);

#endif // SYNCTHREADTESTS_H
