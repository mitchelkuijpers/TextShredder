#include "editlisttests.h"
#include "../textshredder_synchronization_lib/editlist.h"
#include "../textshredder_synchronization_lib/textshredderpacket.h"

void EditListTests::testEmptyConstructor()
{
	EditList *list = new EditList(this);
	unsigned int expectedRemoteVersion = 0;

	QVERIFY2( list != NULL, "EditList should be initialized" );
	QVERIFY2( list->getRemoteVersion() == expectedRemoteVersion,
			  "Remote version should be 0");
	QVERIFY2( list->getEdits().count() == 0, "EditList should have a list with 0 edit objects");

	delete list;
}

void EditListTests::testConstructorWithRemoteVersion()
{
	unsigned int remoteVersion = 97;
	EditList *list = new EditList(this, remoteVersion);

	QVERIFY2( list != NULL, "EditList should be initialized" );
	QVERIFY2( list->getRemoteVersion() == remoteVersion,
			  "Remote version should be " + remoteVersion );

	delete list;
}

void EditListTests::testGetPacketAndConstructorWithPacket()
{
	EditList list(this);
	TextShredderPacket *packet = list.getAllocatedPacket();

	EditList newList(this, *packet);

	QVERIFY2(list == newList, "Lists should be equally -> objects");
	QVERIFY2(list.getEdits().count() == newList.getEdits().count(), "Lists should be equally -> lists");
	QVERIFY2(list.getRemoteVersion() == list.getRemoteVersion (), "Lists should be equally -> version");

	delete packet;
}

void EditListTests::testEmpty()
{
	EditList *list = new EditList(this);
	Edit e(this);
	QVERIFY2(list->isEmpty(), "The EditLists edits should be empty");

	list->addEdit(e);

	QVERIFY2(list->isEmpty() == false, "The EditLists edits should be empty");
}

void EditListTests::testUpdateToRemoteVersion()
{
	Edit zeroEdit(this, 0, NULL);
	Edit oneEdit(this, 1, NULL);
	Edit twoEdit(this, 2, NULL);
	Edit threeEdit(this, 3, NULL);

	EditList editList(this);
	editList.addEdit(zeroEdit);
	editList.addEdit(oneEdit);
	editList.addEdit(twoEdit);
	editList.addEdit(threeEdit);

	QVERIFY2(editList.getEdits().count() == 4, "The EditList edits count should be 4");

	editList.updateToRemoteAndLocalVersion(1, 2);
	QVERIFY2(editList.getRemoteVersion() == 1, "The EditList remote version should be 1");
	QVERIFY2(editList.getEdits().count() == 2, "The EditList edits count should be 2");

	editList.updateToRemoteAndLocalVersion(2, 4);
	QVERIFY2(editList.getRemoteVersion() == 2, "The EditList remote version should be 2");
	QVERIFY2(editList.getEdits().count() == 0, "The EditList edits should contain no edits");
}

void EditListTests::testAddEdit()
{
	const Edit zeroEdit(this, 0, NULL);
	const Edit oneEdit(this, 1, NULL);

	EditList editList(this);

	QVERIFY2(editList.getEdits().count() == 0, "The EditList should not contain edits");

	editList.addEdit(zeroEdit);
	editList.addEdit(oneEdit);

	QVERIFY2( editList.getEdits().count() == 2, "The EditList should contain 2 edits");
	Edit e = editList.getEdits().at(0);
	QVERIFY2( e == zeroEdit, "The EditList first edits object should be zeroEdit");
	e = editList.getEdits().at(1);
	QVERIFY2( e  == oneEdit, "The EditList secon edits object should be oneEdit");
}
