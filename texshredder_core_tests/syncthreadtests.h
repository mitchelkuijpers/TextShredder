#ifndef SYNCTHREADTESTS_H
#define SYNCTHREADTESTS_H

#include <QtCore/QString>
#include "autotest.h"
#include "syncthreadsub.h"
#include <QSharedPointer>
class SyncThreadTests : public QObject
{
    Q_OBJECT

public:
	void setupVariables();
	void breakDownVariables();

	void simpleSyncTest();
	void doubleSyncEditList();
	void multipleEditsOnBothSidesTest();
	void mergedEditsOnBothSidesTest();

private Q_SLOTS:


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
