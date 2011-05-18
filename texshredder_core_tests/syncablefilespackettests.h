#ifndef SYNCABLEFILETESTS_H
#define SYNCABLEFILETESTS_H

#include <QObject>
#include "autotest.h"
#include "../textshredder_core/libraries/network/models/syncablefilespacket.h"

class SyncableFilesPacketTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
		void testFillListWithContentsOfPacket();
};

DECLARE_TEST(SyncableFilesPacketTests)
#endif // SYNCABLEFILETESTS_H
