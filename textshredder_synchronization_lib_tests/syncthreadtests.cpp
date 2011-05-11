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

	breakDownVariables();
}


void SyncThreadTests::doubleSyncEditList()
{
	setupVariables();

	QString beforeText(*leftWorkingCopy->getContent ());
	leftWorkingCopy->getContent ()->append ("d");
	leftSync->pushChanges();

	leftWorkingCopy->getContent ()->append ("e");

	//Create editList and validate state
	EditList leftToRightFirstEditList(*leftEditList);
	//validate leftshadow //localVersion =1 / text is same as working copy
	//validate leftBackup //localVersion =0 / text is beforeText;
	//validate leftEditList //Based version = 0, contains 1 edit. First edit local version = 0
	//optional test patch in edit.

	rightSync->pushChanges();
	EditList rightToLeftFirstEditList(*rightEditList);
	//validate rightShadow //localVersion = 0, remote version = 0 / text is same as working copy
	//validate leftBackup //localVersion =0 / text is same as shadow;
	//validate leftEditList //Based version = 0, contains 0 edit.

	/**
	  * Received First Ack packet on left side
	  */
	leftSync->applyReceivedEditList (rightToLeftFirstEditList);
	//validate leftShadow.con = leftWC.con / leftSh.localVer = 1
	//validate leftBU.local = 0 / leftBu.con = beforeText
	//validate leftEL.rem = 0 /leftEL.contains 1 edit --> (leftEL == leftToRightFIrstEditList)
	//validate leftWC.con == beforeText.append("d").append("e")

	/**
	  * Received First Ack packet on left side
	  */
	rightSync->applyReceivedEditList (leftToRightFirstEditList);
	//validate rightShadow.con = beforeText.append("d")
	//validate rightShadow.loc = 0 / rem = 1;
	//validate rightBackup.con = rightSh.con
	//validate rightBackup.loc = 0;
	//validate rightWC.con = righSh.con
	//validate rightEL.rem = 1


	/**
	  * Make second edit list for left side
	  */
	leftSync->pushChanges ();
	EditList leftToRightSecondEditList(*leftEditList);
	//validate leftWC.con == beforeText.append("d").append("e")
	//validate leftShadow.con = leftWC.con / leftSh.localVer = 2
	//validate leftBU.local = 0 / leftBu.con = beforeText
	//validate leftEL.rem = 0 /leftEL.contains 2 edits
		//Fist edit is +d / on local version 1
		//Second edit is +e / on local version 2


	/**
	  * Make second edit list for right side
	  */
	rightSync->pushChanges();
	EditList rightToLeftSecondEditList(*rightEditList);
	//validate state not changed right side. Do checks on right side as they were before.


	/**
	  * Apply received edit list from left to right.
	  */
	rightSync->applyReceivedEditList (leftToRightSecondEditList);
	//validate rightSh.con == beforeText.append("d").append("e")
	//validate rightSh.rem == 2 / rithSh.loc == 0
	//validate rightBU.con = rightSh.con
	//validate rightBU.loc = 0
	//validate rightWC.con == rightBU.con
	//validate.rightEL.rem == 2
	//validate.rightEl.edits.count == 0

	rightSync->pushChanges ();
	EditList rightToLeftThirdEditList (*rightEditList);
	//Validate state as before on right, the verifies 6 lines above

	leftSync->applyReceivedEditList (rightToLeftSecondEditList);
	//validate leftBU.con == beforeText.append("d")
	//validate leftBU.loc == 1
	//validate leftSh.con == beforeText.append("d").append("e");
	//validate leftSh.loc == 2
	//validate leftSh.rem == 0
	//validate leftWC.con == leftSH.con
	//validate leftEL.edits.count == 1
	//validate leftEL.firstEdit == '+e';

	leftSync->pushChanges();
	EditList leftToRightThirdEditList(*leftEditList);


	breakDownVariables();
}

void SyncThreadTests::writePacketOfEditListTest()
{
	//Should stay empty!!!! At least never call super
}

void SyncThreadTests::setupVariables()
{
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

void SyncThreadTests::breakDownVariables()
{
	//delete leftSync;
	//delete rightSync;

	delete leftWorkingCopy;
	delete rightWorkingCopy;

	leftWorkingCopy = NULL;
	rightWorkingCopy = NULL;
	leftSync = NULL;
	rightSync = NULL;
	leftShadowCopy = NULL;
	rightShadowCopy = NULL;
	leftEditList = NULL;
	rightEditList = NULL;
}
