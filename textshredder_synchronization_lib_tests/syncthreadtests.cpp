#include "syncthreadtests.h"
#include "syncthreadsub.h"


void SyncThreadTests::simpleSyncTest()
{
	setupVariables();

	QString beforeText(*leftWorkingCopy->getContent ());

	leftWorkingCopy->getContent ()->append ("b");
	leftSync->pushChanges();

	EditList editList(*leftEditList);
	rightSync->applyReceivedEditList (editList);

	//validate leftshadow //localVersion =1 / text is same as working copy
	//validate leftBackup //localVersion =0 / text is beforeText;
	//validate leftEditList //Based version = 0, contains 1 edit. First edit local version = 0
	//optional test patch in edit.

	//validate rightShadow.content == leftSh.content. rithSH.rem = 1, loc =0
	//validate rightShadow.con == rightBackup.content
	//validate rightBU.loc = 0;
	//validate rightWC.con == righSh.con
	//validate rightEdit.rem = 1
	//validate rightEdit.edits.count = 0

	rightSync->pushChanges();
	EditList ackEditList(*rightEditList);
	leftSync->applyReceivedEditList (ackEditList);

	//validate leftshadow //localVersion =1 / text is same as working copy
	//validate leftBackup //localVersion = 1 / text is leftSH.con;
	//validate leftEditList //Based version = 0, contains 0 edits.  count = 0

}


void SyncThreadTests::pushChangesTest()
{
}

void SyncThreadTests::writePacketOfEditListTest()
{
	//Should stay empty!!!! At least never call super
}

void SyncThreadTests::setupVariables() {
	QString startText("abc");

	leftWorkingCopy = new WorkingCopy(this);
	leftWorkingCopy->getContent()->append (startText);
	rightWorkingCopy = new WorkingCopy(this);
	rightWorkingCopy->getContent()->append (startText);

	TextShredderConnection conn(this, -1);
	leftSync = new SyncThreadSub(this, conn, *leftWorkingCopy);
	rightSync = new SyncThreadSub(this, conn, *rightWorkingCopy);

	leftShadowCopy = leftSync->getShadowCopy ();
	rightShadowCopy = rightSync->getShadowCopy ();

	leftEditList = leftSync->getEditList ();
	rightEditList = rightSync->getEditList ();
}
