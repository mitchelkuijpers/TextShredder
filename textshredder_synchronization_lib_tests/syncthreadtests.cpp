#include "syncthreadtests.h"
#include "syncthreadsub.h"

#include <QtCore>
void SyncThreadTests::simpleSyncTest()
{
	setupVariables();

	QString beforeText(*leftWorkingCopy->getContent ());

	leftWorkingCopy->getContent ()->append ("b");
	leftSync->pushChanges();

	EditList editList(*leftEditList);
	rightSync->applyReceivedEditList (editList);

	//validate leftshadow //localVersion =1 / text is same as working copy
	QVERIFY2(leftShadowCopy->getLocalVersion() == 1, "leftShadowCopy localversion is not 1");
	QVERIFY2(*leftShadowCopy->getContent() == *leftWorkingCopy->getContent(),
	 "ShadowCopy content is not equal to WorkingCopyContent");

	//validate leftBackup //localVersion =0 / text is beforeText;
	QVERIFY2(leftShadowCopy->getBackupCopy()->getLocalVersion() == 0,
	 "BackupVersion != 0");


	QVERIFY2((*leftShadowCopy->getBackupCopy()->getContent()) == beforeText,
		 "BackupCopy content != beforeText");

	//validate leftEditList //Based version = 0, contains 1 edit. First edit local version = 0
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
		 "LeftEditList version != 0");
	QVERIFY2(leftEditList->getEdits().size() == 1,
		 "LeftEditList != contains 1 edit");
	QVERIFY2(leftEditList->getEdits().first().getLocalVersion() == 0,
		 "First edit local version != 0");

	//optional test patch in edit.

	//validate rightShadow.content == leftSh.content. rithSH.rem = 1, loc =0
	QVERIFY2(*rightShadowCopy->getContent() == *leftShadowCopy->getContent(),
		"rightshadowcopy content != leftshadowcopy content");
	QVERIFY2(rightShadowCopy->getRemoteVersion() == 1,
		 "rightshadowcopy remoteVersion != 1");
	QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
		 "rightshadowcopy localversion != 0");

	//validate rightShadow.con == rightBackup.content
	QVERIFY2(*rightShadowCopy->getContent() == *rightShadowCopy->getBackupCopy()->getContent(),
		 "rightshadow content != rightbackup content");

	//validate rightBU.loc = 0;
	QVERIFY2(rightShadowCopy->getBackupCopy()->getLocalVersion() == 0,
		 "backupcopy localversion != 0");

	//validate rightWC.con == righSh.con
	QVERIFY2(*rightWorkingCopy->getContent() == *rightShadowCopy->getContent(),
		 "rightworkingcopy content != rightshadowcopy content");

	//validate rightEdit.rem = 1
	QVERIFY2(rightEditList->getRemoteVersion() == 1,
		 "rightEditList remoteversion != 1");

	//validate rightEdit.edits.count = 0
	QVERIFY2(rightEditList->getEdits().count() == 0,
		 "rightEditList count != 0");

	rightSync->pushChanges();
	EditList ackEditList(*rightEditList);
	leftSync->applyReceivedEditList (ackEditList);

	//validate leftshadow //localVersion =1 / text is same as working copy

	QString messageName("leftshadowcopy content != leftWorkingcopy content");
	messageName.append(leftShadowCopy->getLocalVersion());
	messageName.append(*leftWorkingCopy->getContent());
	qDebug() << QString::number(leftShadowCopy->getLocalVersion());

	QVERIFY2(leftEditList->isEmpty(), "The left editlist should be empty. All are acked.");
	QVERIFY2(leftShadowCopy->getLocalVersion() == 1,
			 "leftshadowcopy localversion != 1");
	QVERIFY2((*leftShadowCopy->getContent()) == (*leftWorkingCopy->getContent()),
			 messageName.toStdString().c_str());

	//validate leftBackup //localVersion = 1 / text is leftSH.con;
		QVERIFY2(leftShadowCopy->getBackupCopy()->getLocalVersion() ==1,
				 "backupcopy localversion != 1");
		QVERIFY2(*leftShadowCopy->getBackupCopy()->getContent() == *leftShadowCopy->getContent(),
				 "leftbackupcopy content != shadowcopy content");

	//validate leftEditList //Based version = 0, contains 0 edits.  count = 0
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
				 "leftEditList remoteversion != 0");
	QVERIFY2(leftEditList->isEmpty(),
				 "left editlist != empty");

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
	//validate leftEL.rem == 0
	//validate leftEL.edits.count == 1
	//validate leftEL.firstEdit == '+e'; //loc = 2

	leftSync->pushChanges();
	EditList leftToRightThirdEditList(*leftEditList);
	//validate leftBU.con == beforeText.append("d")
	//validate leftBU.loc == 1
	//validate leftSh.con == beforeText.append("d").append("e");
	//validate leftSh.loc == 2
	//validate leftSh.rem == 0
	//validate leftWC.con == leftSH.con
	//validate leftEL.rem == 0
	//validate leftEL.edits.count == 1
	//validate leftEL.firstEdit == '+e';//loc = 2

	/**
	  * Apply third and final ack packet on left side.
	  */
	leftSync->applyReceivedEditList (rightToLeftThirdEditList);
	//validate leftBU.con == beforeText.append("d").append("e");
	//validate leftSh.con == beforeText.append("d").append("e");
	//validate leftWC.con == beforeText.append("d").append("e");
	//validate leftBU.loc == 2
	//validate leftSh.loc == 2
	//validate leftSh.rem == 0
	//validate leftEL.rem == 0
	//validate leftEL.edits.count == 0
	//validate leftEL.firstEdit == '+e'; //loc = 2

	/**
	  * Apply third and final packet on right side
	  */
	rightSync->applyReceivedEditList (leftToRightSecondEditList);
	//validate rightSh.con == beforeText.append("d").append("e")
	//validate rightBU.con == rightSh.con
	//validate rightWC.con == rightSh.con
	//validate rightSh.rem == 2 / rithSh.loc == 0
	//validate rightBU.loc = 0
	//validate.rightEL.rem == 2
	//validate.rightEl.edits.count == 0

	breakDownVariables();
}

void SyncThreadTests::multipleEditsOnBothSidesTest()
{
	setupVariables();
	//both are 'abc'
	QString beforeText(*leftWorkingCopy->getContent ());

	//left is 'abcd'
	leftWorkingCopy->getContent ()->append ("def");
	leftSync->pushChanges();
	EditList leftToRightFirstEditList(*leftEditList);

	QVERIFY(leftShadowCopy->getLocalVersion() == 1);
	QVERIFY(leftShadowCopy->getRemoteVersion() == 0);
	QVERIFY(leftShadowCopy->getBackupCopy()->getLocalVersion() == 0);
	QVERIFY(*leftShadowCopy->getContent() == *leftWorkingCopy->getContent());
	QVERIFY(*leftShadowCopy->getBackupCopy ()->getContent () == beforeText);

	//right is ''
	(*rightWorkingCopy->getContent ()) = "";
	rightSync->pushChanges ();
	EditList rightToLeftFirstEditList(*rightEditList);

	QVERIFY(rightShadowCopy->getLocalVersion() == 1);
	QVERIFY(rightShadowCopy->getRemoteVersion() == 0);
	QVERIFY(rightShadowCopy->getBackupCopy()->getLocalVersion() == 0);
	QVERIFY(*rightShadowCopy->getContent() == *rightWorkingCopy->getContent());
	QVERIFY(*rightShadowCopy->getBackupCopy ()->getContent () == beforeText);

	leftSync->applyReceivedEditList (rightToLeftFirstEditList);
	rightSync->applyReceivedEditList (leftToRightFirstEditList);
	QVERIFY(leftShadowCopy->getRemoteVersion() == 1);
	QVERIFY(leftShadowCopy->getLocalVersion() == 1);

	QVERIFY(leftShadowCopy->getBackupCopy()->getLocalVersion() == 0);
	QVERIFY(*leftShadowCopy->getBackupCopy()->getContent() == "");
	QVERIFY(*leftShadowCopy->getContent () == "d");
	QVERIFY(*leftShadowCopy->getContent () == *leftWorkingCopy->getContent());

	QVERIFY(rightShadowCopy->getRemoteVersion () == 1);



	leftSync->pushChanges();

	EditList leftToRightSecondEditLIst(*leftEditList);
	rightSync->pushChanges ();
	EditList rightToLeftSecondEditList(*rightEditList);

	leftSync->applyReceivedEditList(rightToLeftSecondEditList);

	rightSync->applyReceivedEditList(leftToRightSecondEditLIst);

	//Validate:

	qDebug() << (*leftShadowCopy->getContent ());
	qDebug() << (*leftWorkingCopy->getContent ());
	//leftWC.con == leftSh.con == leftBU.con == rightWC.con == rightSH.con == rightBU.con
	QVERIFY2((*leftWorkingCopy->getContent ()) == (*leftShadowCopy->getContent()),
			 "Left working copy should be equal to its shadow copy");
	QVERIFY2((*leftWorkingCopy->getContent ()) == (*leftShadowCopy->getBackupCopy()->getContent()),
			 "Left working copy should be equal to the backup copy");
	QVERIFY2((*rightWorkingCopy->getContent ()) == (*rightShadowCopy->getContent()),
			 "Right working copy should be equal to its shadow copy");
	QVERIFY2((*rightWorkingCopy->getContent ()) == (*rightShadowCopy->getBackupCopy()->getContent()),
			 "Right working copy should be equal to the backup copy");
	QVERIFY2((*leftWorkingCopy->getContent()) == (*rightWorkingCopy->getContent()),
			 "Both working copies should be equal");

	//leftSh.loc == 1 / leftSh.rem = 1
	QVERIFY2(leftShadowCopy->getLocalVersion() == 1,
			 "The local version of the left shadow copy should be equal to 1");
	QVERIFY2(leftShadowCopy->getRemoteVersion() == 1,
			 "The remote version of the left shadow copy should be equal to 1");

	//rightSh.loc == 1 / rightSh.rem = 1
	QVERIFY2(rightShadowCopy->getLocalVersion() == 1,
			 "The local version of the right shadow copy should be equal to 1");
	QVERIFY2(rightShadowCopy->getRemoteVersion() == 1,
			 "The remote version of the right shadow copy should be equal to 1");

	//leftBU.loc == 1
	QVERIFY2(leftShadowCopy->getBackupCopy()->getLocalVersion() == 1,
			 "The local vesion of the backup on the left side should be equal to 1");

	//rightBU.loc == 1
	QVERIFY2(rightShadowCopy->getBackupCopy()->getLocalVersion() == 1,
			 "The local vesion of the backup on the left side should be equal to 1");

	//leftEL.count == 0
	QVERIFY2(leftEditList->getEdits().count() == 0,
			 "The left side should not have edits");

	//leftEL.rem == 1
	QVERIFY2(leftEditList->getRemoteVersion() == 1,
			 "The left side editList should have a remote version of 1");

	//rightEL.count == 0
	QVERIFY2(rightEditList->getEdits().count() == 0,
			 "The left side should not have edits");

	//rightEL.rem == 1
	QVERIFY2(rightEditList->getRemoteVersion() == 1,
			 "The right side editList should have a remote version of 1");
}

void SyncThreadTests::mergedEditsOnBothSidesTest()
{
	setupVariables();

	QString beforeText(*leftWorkingCopy->getContent ());
	leftWorkingCopy->getContent ()->append ("123");
	leftSync->pushChanges();
	EditList leftToRightFirstEditList(*leftEditList);

	rightWorkingCopy->getContent ()->append("456");
	rightSync->pushChanges ();
	EditList rightToLeftFirstEditList(*rightEditList);

	leftSync->applyReceivedEditList (rightToLeftFirstEditList);
	rightSync->applyReceivedEditList (leftToRightFirstEditList);

	leftSync->pushChanges();
	EditList leftToRightSecondEditList(*leftEditList);
	rightSync->pushChanges ();
	EditList rightToLeftSecondEditList(*rightEditList);

	leftSync->applyReceivedEditList(rightToLeftSecondEditList);
	rightSync->applyReceivedEditList(leftToRightSecondEditList);

	QString leftText(*leftWorkingCopy->getContent ());
	QString rightText(*leftWorkingCopy->getContent ());
	QString expectedTextOne = beforeText;
	expectedTextOne.append("123").append("456");
	QString expectedTextTwo = beforeText;
	expectedTextTwo.append("456").append("123");

	// leftWC.con == rightSh.con == beforeText.append("123").append("456")
	// OR
	// leftWC.con == rightSh.con == beforeText.append("456").append("123")
//	qDebug() << leftText;
//	qDebug() << rightText;
//	qDebug() << expectedTextOne;
//	qDebug() << expectedTextTwo;
	QVERIFY2(leftText == rightText, "Working copy content for left and right should be equal.");
	if ((leftText == expectedTextOne || leftText == expectedTextTwo) == false) {
		QVERIFY2(false, "The text should be atleast one of the expected texts");
	}
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
