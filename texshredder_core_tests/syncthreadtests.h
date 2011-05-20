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
	void breakDownVariables();

private Q_SLOTS:
	void simpleSyncTest();
	void doubleSyncEditList();
	void multipleEditsOnBothSidesTest();
	void mergedEditsOnBothSidesTest();

private:
	void doDeleteWorkingCopy(WorkingCopy *obj);

	SyncThreadSub *leftSync;
	SyncThreadSub *rightSync;

	QSharedPointer<WorkingCopy> leftWorkingCopyPointer;
	WorkingCopy *leftWorkingCopy;
	QSharedPointer<WorkingCopy> rightWorkingCopyPointer;
	WorkingCopy *rightWorkingCopy;

	ShadowCopy *leftShadowCopy;
	ShadowCopy *rightShadowCopy;

	EditList *leftEditList;
	EditList *rightEditList;
};

DECLARE_TEST(SyncThreadTests);

#endif // SYNCTHREADTESTS_H
