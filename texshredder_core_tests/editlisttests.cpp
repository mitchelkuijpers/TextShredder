#include "editlisttests.h"
#include "../textshredder_core/libraries/synchronization/models/editlist.h"
#include "../textshredder_core/libraries/network/models/textshredderpacket.h"
#include "../textshredder_core/libraries/diff_match_patch/diff_match_patch.h"

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
	diff_match_patch dmp;

	QString s("@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n");
	QList<Patch> pList1 = dmp.patch_fromText(s);
	QList<Patch> pList2 = dmp.patch_fromText(s);

	Edit e1(this, 400, pList1);
	Edit e2(this, 255, pList2);

	list.addEdit(e1);
	list.addEdit(e2);

	TextShredderPacket *packet = list.getAllocatedPacket();

	EditList newList(this, *packet);
	QVERIFY2(newList.getRemoteVersion() == list.getRemoteVersion(), "AAA");

	QVERIFY2(list == newList, "TFU");
	QVERIFY2(list.getEdits().count() == newList.getEdits().count(), "Lists should be equally -> lists");
	for(int i = 0; i < list.getEdits().count(); i++) {
		Edit originalEditObject = list.getEdits ().at(i);
		Edit newEditObject = newList.getEdits ().at(i);

		QVERIFY2(newEditObject.getLocalVersion () == originalEditObject.getLocalVersion(), "Local versions of edits should be equal");
		QVERIFY2(newEditObject.getPatches () == originalEditObject.getPatches(), "CRAP");
	}
	//QVERIFY2(false, "Still have to implement test");

	//delete packet;
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
	QList<Patch> list;
	Edit zeroEdit(this, 0, list);
	Edit oneEdit(this, 1, list);
	Edit twoEdit(this, 2, list);
	Edit threeEdit(this, 3, list);

	EditList editList(this);
	editList.addEdit(zeroEdit);
	editList.addEdit(oneEdit);
	editList.addEdit(twoEdit);
	editList.addEdit(threeEdit);

	QVERIFY2(editList.getEdits().count() == 4, "The EditList edits count should be 4");

	editList.updateToRemote(1);
	QVERIFY2(editList.getRemoteVersion() == 1, "The EditList remote version should be 1");

	editList.updateToRemote(2);
	QVERIFY2(editList.getRemoteVersion() == 2, "The EditList remote version should be 2");
}

void EditListTests::testAddEdit()
{
	QList<Patch> list;
	const Edit zeroEdit(this, 0, list);
	const Edit oneEdit(this, 1, list);

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

void EditListTests::testPopEditsUpToLocalVersion()
{
	QList<Patch> list;
	Edit firstEdit(this, 0, list);
	Edit secondEdit(this, 1, list);
	Edit thirdEdit(this, 2, list);

	EditList editList(this);
	editList.addEdit(firstEdit);

	editList.popEditsUpToLocalVersion(5);
	QVERIFY2(firstEdit.getLocalVersion() == 5, "The firstEdit should return 5");

}
