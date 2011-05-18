#ifndef FILEMANAGERTEST_H
#define FILEMANAGERTEST_H

#include <QObject>
#include "autotest.h"
#include "../textshredder_core/libraries/synchronization/filemanager.h"

class FileManagerTest : public QObject
{
    Q_OBJECT

private:

private Q_SLOTS:
	void testHandleReceivedSyncableFiles();
	void testHandleReceivedSyncableFilesWithChangedAlias();
};


DECLARE_TEST(FileManagerTest);
#endif // FILEMANAGERTEST_H
