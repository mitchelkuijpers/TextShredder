#ifndef FILEREQUESTPACKETTEST_H
#define FILEREQUESTPACKETTEST_H

#include <QObject>
#include "autotest.h"

class FileRequestPacketTest : public QObject
{
    Q_OBJECT

private:

private Q_SLOTS:
	void testGetPort();

};

DECLARE_TEST(FileRequestPacketTest);

#endif // FILEREQUESTPACKETTEST_H
