#ifndef FILEDATAPACKETTEST_H
#define FILEDATAPACKETTEST_H

#include <QObject>
#include "autotest.h"

class FileDataPacketTest : public QObject
{
	Q_OBJECT

private:

private Q_SLOTS:
	void testGetRemoteFileHandle();
	void testGetFileDataContent();
};

DECLARE_TEST(FileDataPacketTest);

#endif // FILEDATAPACKETTEST_H
