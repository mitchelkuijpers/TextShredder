#ifndef SYNCTHREADTESTS_H
#define SYNCTHREADTESTS_H

#include <QtCore/QString>
#include "autotest.h"


class SyncThreadTests : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void processChangesTest();
    void pushChangesTest();
    void writePacketOfEditListTest();


};

DECLARE_TEST(SyncThreadTests);

#endif // SYNCTHREADTESTS_H
