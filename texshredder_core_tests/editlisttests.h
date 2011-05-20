#ifndef EDITLISTTESTS_H
#define EDITLISTTESTS_H

#include <QtCore/QtCore>
#include "autotest.h"

class EditListTests: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void testEmptyConstructor();
	void testConstructorWithRemoteVersion();
	void testGetPacketAndConstructorWithPacket();
	void testEmpty();
	void testUpdateToRemoteVersion();
	void testAddEdit();
	void testPopEditsUpToLocalVersion();
};

DECLARE_TEST(EditListTests)

#endif // EDITLISTTESTS_H
