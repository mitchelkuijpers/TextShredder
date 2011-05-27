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
//	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 0, "BackupVersion != 0");


	QVERIFY2((*leftShadowCopy->getBackupCopy().getContent()) == beforeText,
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
	QVERIFY2(*rightShadowCopy->getContent() == *rightShadowCopy->getBackupCopy().getContent(),
		 "rightshadow content != rightbackup content");

	//validate rightBU.loc = 0;
	QVERIFY2(rightShadowCopy->getBackupCopy().getLocalVersion() == 0,
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

	QVERIFY2(leftEditList->isEmpty(), "The left editlist should be empty. All are acked.");
	QVERIFY2(leftShadowCopy->getLocalVersion() == 1,
			 "leftshadowcopy localversion != 1");
	QVERIFY2((*leftShadowCopy->getContent()) == (*leftWorkingCopy->getContent()),
			 messageName.toStdString().c_str());

	//validate leftBackup //localVersion = 1 / text is leftSH.con;
		QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() ==1,
				 "backupcopy localversion != 1");
		QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == *leftShadowCopy->getContent(),
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
	QVERIFY2(leftShadowCopy->getLocalVersion() == 1,
			 "leftshadowcopy != 1");


	QVERIFY2(*leftShadowCopy->getContent() == (beforeText +"d"),
			 "leftshadowcopy content != (beforeText +d)");
	QVERIFY2(*leftWorkingCopy->getContent() == (beforeText +"de"),
			 "leftWorkingCopy content != (beforeText +de)");

	//validate leftBackup //localVersion =0 / text is beforeText;
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 0,
			 "leftbackupcopy != 0");
	QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == beforeText,
			 "left backupcopy != beforetext");

	//validate leftEditList //Based version = 0, contains 1 edit. First edit local version = 0
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
			 "leftEditList remoeversion != 0");
	QVERIFY2(leftEditList->getEdits().count() == 1,
			 "leftEditList should contain 1 edit");
	//validate leftBackup //localVersion =0 / text is same as shadow;
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 0,
			 "leftbackupcopy != 0");
	QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == beforeText,
			 "leftbackupcopy content != leftshadowcontent");
	//validate leftEditList //Based version = 0, contains 0 edit.
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
			 "leftEditList based on version != 0");

	rightSync->pushChanges();
	EditList rightToLeftFirstEditList(*rightEditList);
	//validate rightShadow //localVersion = 0, remote version = 0 / text is same as working copy
	QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
			 "rightshadowcopy localversion != 0");
	QVERIFY2(rightShadowCopy->getRemoteVersion() == 0,
			 "rightshadowcopy remoteversion != 0");
	QVERIFY2(*rightShadowCopy->getContent() == *rightWorkingCopy->getContent(),
			 "rightShadowCopy content != right workingcopy content");

	/**
	  * Received First Ack packet on left side
	  */
	leftSync->applyReceivedEditList (rightToLeftFirstEditList);

	//validate leftShadow.con = leftWC.con / leftSh.localVer = 1
	QVERIFY2(*leftShadowCopy->getContent() == beforeText+"d",
			 "shadowcopycontent != workingcopycontent");
	QVERIFY2(leftShadowCopy->getLocalVersion() == 1,
			 "shadowcopy localversion != 1");

	//validate leftBU.local = 0 / leftBu.con = beforeText
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 0,
			 "leftbackupversion != 0");
	QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == beforeText,
			 "leftbackupcopy content != beforetext");

	//validate leftEL.rem = 0 /leftEL.contains 1 edit --> (leftEL == leftToRightFIrstEditList)
	QVERIFY2(*leftEditList == leftToRightFirstEditList,
			 "leftEditList != leftToRightFirstEditList");

	//validate leftWC.con == beforeText.append("d").append("e")
	QVERIFY2(*leftWorkingCopy->getContent() == (beforeText + "de"),
			 "leftWorkingCopy content != (beforeText + de)");

	/**
	  * Received First Ack packet on right side
	  */
	rightSync->applyReceivedEditList (leftToRightFirstEditList);
	//validate rightShadow.con = beforeText.append("d")
	QVERIFY2(*rightShadowCopy->getContent() == (beforeText + "d"),
			 "rightshadowCopy content != (beforeText +d)");

	//validate rightShadow.loc = 0 / rem = 1;
	QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
			 "rightShadowCopy localversion != 0");
	QVERIFY2(rightShadowCopy->getRemoteVersion() == 1,
			 "rightShadowCopy remoteversion != 1");

	//validate rightBackup.con = rightSh.con
	QVERIFY2(*rightShadowCopy->getBackupCopy().getContent() == *rightShadowCopy->getContent(),
			 "rightbackupcopy content != rightShadowCopy content");

	//validate rightBackup.loc = 0;
	QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
			 "rightShadowCopy localversion != 0");

	//validate rightWC.con = righSh.con
	QVERIFY2(*rightWorkingCopy->getContent() == *rightShadowCopy->getContent(),
			 "rightWorkingCopy content != rightShadowCopy content");

	//validate rightEL.rem = 1
	QVERIFY2(rightEditList->getRemoteVersion() == 1,
			 "rightEditList remotversion != 1");


	/**
	  * Make second edit list for left side
	  */
	leftSync->pushChanges();
	EditList leftToRightSecondEditList(*leftEditList);
	//validate leftWC.con == beforeText.append("d").append("e")
	QVERIFY2(*leftWorkingCopy->getContent() == (beforeText + "de"),
			 "leftworkingcopy content != (beforeText + de)");

	//validate leftShadow.con = leftWC.con / leftSh.localVer = 2
	QVERIFY2(*(leftShadowCopy->getContent()) == *(leftWorkingCopy->getContent()),
			 "leftshadowcopy content != leftWorkingCopy content");

	//validate leftBU.local = 0 / leftBu.con = beforeText
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 0,
			 "leftBackupCopy localversion != 0");

	//validate leftEL.rem = 0 /leftEL.contains 2 edits
		//Fist edit is +d / on local version 1
		//Second edit is +e / on local version 2
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
			 "leftEditList remoteversion != 0");
	QVERIFY2(leftEditList->getEdits().count() == 2,
			 "leftEditList != contains 2 edits");
	QVERIFY2(leftEditList->getEdits().first() == leftToRightFirstEditList.getEdits().first(),
			 "unacked edit changed");

	QVERIFY2(((Edit) leftEditList->getEdits().at(0)).getLocalVersion() == 0,
			 "first edit != localversion 0");
	QVERIFY2(((Edit) leftEditList->getEdits().at(1)).getLocalVersion() == 1,
			 "second edit != localversion 1");


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
	QVERIFY2(*rightShadowCopy->getContent() == beforeText + ("de"),
			 "rightShadowCopy content != (beforetext + de)");

	//validate rightSh.rem == 2 / rithSh.loc == 0
	QVERIFY2(rightShadowCopy->getRemoteVersion() == 2,
			 "rightShadowCopy remoteversion != 2");
	QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
			 "rightShadowCopy localversion != 0");

	//validate rightBU.con = rightSh.con
	QVERIFY2(*rightShadowCopy->getBackupCopy().getContent() == *rightShadowCopy->getContent(),
			 "rightBackupCopy content != rightShadowCopy");

	//validate rightBU.loc = 0
	QVERIFY2(rightShadowCopy->getBackupCopy().getLocalVersion() == 0,
			 "rightbackupcopyr != 0");

	//validate rightWC.con == rightBU.con
	QVERIFY2(*rightWorkingCopy->getContent() == *rightShadowCopy->getBackupCopy().getContent(),
			 "rightworkingcopy content != rightbackupcopy content");

	//validate.rightEL.rem == 2
	QVERIFY2(rightEditList->getRemoteVersion() == 2,
			 "rightEditList remoteversion != 2");

	//validate.rightEl.edits.count == 0
	QVERIFY2(rightEditList->isEmpty(), "rightEditList != empty");

	rightSync->pushChanges ();
	EditList rightToLeftThirdEditList (*rightEditList);
	//Validate state as before on right, the verifies 6 lines above


	leftSync->applyReceivedEditList (rightToLeftSecondEditList);
	//validate leftBU.con == beforeText.append("d")
	QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == (beforeText +"d"),
			 "LeftBackupCopy content != (beforeText + d)");

	//validate leftBU.loc == 1
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 1,
			 "leftBackupCopy localversion != 1");

	//validate leftSh.con == beforeText.append("d").append("e");
	QVERIFY2(*leftShadowCopy->getContent() == (beforeText +"de"),
			 "leftShadowCopy content != (beforeText + de)");

	//validate leftSh.loc == 2
	QVERIFY2(leftShadowCopy->getLocalVersion() == 2,
			 "leftShadowCopy localversion != 2");

	//validate leftSh.rem == 0
	QVERIFY2(leftShadowCopy->getRemoteVersion() == 0,
			 "leftShadowCopy remoteversion != 0");

	//validate leftWC.con == leftSH.con
	QVERIFY2(*leftWorkingCopy->getContent() == *leftShadowCopy->getContent(),
			 "leftWorkingCopy content != leftShadowCopy content");

	//validate leftEL.rem == 0
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
			 "leftEditList != 0");

	//validate leftEL.edits.count == 1
	QVERIFY2(leftEditList->getEdits().count() == 1,
			 "leftEditList totaledits != 1");

	//validate leftEL.firstEdit == '+e'; //loc = 2
	QVERIFY2(leftEditList->getEdits().first() == leftToRightSecondEditList.getEdits().at(1),
			 "unacked edit changed");


	leftSync->pushChanges();
	EditList leftToRightThirdEditList(*leftEditList);
	//validate leftBU.con == beforeText.append("d")
	QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == (beforeText + "d"),
			 "leftBackUpcopy != (beforeText +d)");

	//validate leftBU.loc == 1
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 1,
			 "leftBackupCopy != 1");

	//validate leftSh.con == beforeText.append("d").append("e");
	QVERIFY2(*leftShadowCopy->getContent() == (beforeText + "de"),
			 "leftShadowCopy content != (beforeText +de)");

	//validate leftSh.loc == 2
	QVERIFY2(leftShadowCopy->getLocalVersion() == 2,
			 "leftShadowCopy localversion != 2");

	//validate leftSh.rem == 0
	QVERIFY2(leftShadowCopy->getRemoteVersion() == 0,
			 "leftShadowCopy remoteversion != 0");

	//validate leftWC.con == leftSH.con
	QVERIFY2(*leftWorkingCopy->getContent() == *leftShadowCopy->getContent(),
			 "leftWorkingCopy content != leftShadowCopy content");

	//validate leftEL.rem == 0
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
			 "leftEditList remoteversion != 0");

	//validate leftEL.edits.count == 1
	QVERIFY2(leftEditList->getEdits().count() == 1,
			 "leftEditList size != 1");

	//validate leftEL.firstEdit == '+e';//loc = 2
	QVERIFY2(leftEditList->getEdits().first() == leftToRightSecondEditList.getEdits().at(1),
			 "leftEditList first edit != +e");

	/**
	  * Apply third and final ack packet on left side.
	  */
	leftSync->applyReceivedEditList (rightToLeftThirdEditList);
	//validate leftBU.con == beforeText.append("d").append("e");
	QVERIFY2(*leftShadowCopy->getBackupCopy().getContent() == (beforeText + "de"),
			 "leftBackupcopy content != (beforeText +de)");

	//validate leftSh.con == beforeText.append("d").append("e");
	QVERIFY2(*leftShadowCopy->getContent() == (beforeText + "de"),
			 "leftShadowCopy content != (beforeText +de)");

	//validate leftWC.con == beforeText.append("d").append("e");
	QVERIFY2(*leftWorkingCopy->getContent() == (beforeText + "de"),
			 "leftWorkingCopy content != (beforeText +de)");

	//validate leftBU.loc == 2
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 2,
			 "leftBackupCopy localversion != 2");


	//validate leftSh.loc == 2
	QVERIFY2(leftShadowCopy->getLocalVersion() == 2,
			 "leftShadowCopy != 2");

	//validate leftSh.rem == 0
	QVERIFY2(leftShadowCopy->getRemoteVersion() == 0,
			 "leftShadowCopy remotversion != 0");

	//validate leftEL.rem == 0
	QVERIFY2(leftEditList->getRemoteVersion() == 0,
			 "leftEditList remoteversion != 0");

	//validate leftEL.edits.count == 0
	QVERIFY2(leftEditList->isEmpty(),
			 "leftEditList != empty");


	/**
	  * Apply third and final packet on right side
	  */

	rightSync->applyReceivedEditList (leftToRightSecondEditList);
	//validate rightSh.con == beforeText.append("d").append("e")
	QVERIFY2(*rightShadowCopy->getContent() == (beforeText + "de"),
			 "rightShadowCopy content != (beforeText + de)");

	//validate rightBU.con == rightSh.con
	QVERIFY2(*rightShadowCopy->getBackupCopy().getContent() == *rightShadowCopy->getContent(),
			 "rightBackupCopy content != rightShadowCopy content");

	//validate rightWC.con == rightSh.con
	QVERIFY2(*rightWorkingCopy->getContent() == *rightShadowCopy->getContent(),
			 "rightWorkingCopy != rightShadowCopy");

	//validate rightSh.rem == 2 / rithSh.loc == 0
	QVERIFY2(rightShadowCopy->getRemoteVersion() == 2,
			 "rightShadowCopy remoteversion != 2");
	QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
			 "rightShadowCopy localversion != 0");

	//validate rightBU.loc = 0
	QVERIFY2(rightShadowCopy->getBackupCopy().getLocalVersion() == 0,
			 "righBackupCopy != 0");

	//validate.rightEL.rem == 2
	QVERIFY2(rightEditList->getRemoteVersion() == 2,
			 "rightEditList remoteversion != 2");

	//validate.rightEl.edits.count == 0
	QVERIFY2(rightEditList->isEmpty(),
			 "rightEditList != empty");

	breakDownVariables();
}

void SyncThreadTests::multipleEditsOnBothSidesTest()
{
	setupVariables();
	//both are 'abc'
	QString beforeText(*leftWorkingCopy->getContent ());

	//left is 'abcd'
	leftWorkingCopy->getContent ()->append ("d");
	leftSync->pushChanges();
	EditList leftToRightFirstEditList(*leftEditList);

	QVERIFY(leftShadowCopy->getLocalVersion() == 1);
	QVERIFY(leftShadowCopy->getRemoteVersion() == 0);
	QVERIFY(leftShadowCopy->getBackupCopy().getLocalVersion() == 0);
	QVERIFY(*leftShadowCopy->getContent() == *leftWorkingCopy->getContent());
	QVERIFY(*leftShadowCopy->getBackupCopy().getContent () == beforeText);

	//right is ''
	(*rightWorkingCopy->getContent ()) = "";
	rightSync->pushChanges ();
	EditList rightToLeftFirstEditList(*rightEditList);
	QVERIFY(rightShadowCopy->getLocalVersion() == 1);
	QVERIFY(rightShadowCopy->getRemoteVersion() == 0);
	QVERIFY(rightShadowCopy->getBackupCopy().getLocalVersion() == 0);
	QVERIFY(*rightShadowCopy->getContent() == *rightWorkingCopy->getContent());
	QVERIFY(*rightShadowCopy->getBackupCopy().getContent () == beforeText);

	leftSync->applyReceivedEditList (rightToLeftFirstEditList);

	rightSync->applyReceivedEditList (leftToRightFirstEditList);

	QVERIFY(leftShadowCopy->getRemoteVersion() == 1);
	QVERIFY(leftShadowCopy->getLocalVersion() == 1);
	QVERIFY(leftShadowCopy->getBackupCopy().getLocalVersion() == 0);
	QVERIFY(*leftShadowCopy->getBackupCopy().getContent() == "");
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

	//leftWC.con == leftSh.con == leftBU.con == rightWC.con == rightSH.con == rightBU.con
	QVERIFY2((*leftWorkingCopy->getContent ()) == (*leftShadowCopy->getContent()),
			 "Left working copy should be equal to its shadow copy");
	QVERIFY2((*leftWorkingCopy->getContent ()) == (*leftShadowCopy->getBackupCopy().getContent()),
			 "Left working copy should be equal to the backup copy");
	QVERIFY2((*rightWorkingCopy->getContent ()) == (*rightShadowCopy->getContent()),
			 "Right working copy should be equal to its shadow copy");
	QVERIFY2((*rightWorkingCopy->getContent ()) == (*rightShadowCopy->getBackupCopy().getContent()),
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
	QVERIFY2(leftShadowCopy->getBackupCopy().getLocalVersion() == 1,
			 "The local vesion of the backup on the left side should be equal to 1");

	//rightBU.loc == 1
	QVERIFY2(rightShadowCopy->getBackupCopy().getLocalVersion() == 1,
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
	QVERIFY2(leftText == rightText, "Working copy content for left and right should be equal.");
	if ((leftText == expectedTextOne || leftText == expectedTextTwo) == false) {
		QVERIFY2(false, "The text should be atleast one of the expected texts");
	}
}


void SyncThreadTests::doDeleteWorkingCopy(WorkingCopy *obj)
{
	obj->deleteLater();
}

void SyncThreadTests::setupVariables()
{
	QString startText("abc");

	leftWorkingCopyPointer = QSharedPointer<WorkingCopy> (new WorkingCopy(this));
	leftWorkingCopy = leftWorkingCopyPointer.data();
	leftWorkingCopy->getContent()->append (startText);

	rightWorkingCopyPointer = QSharedPointer<WorkingCopy> (new WorkingCopy(this));
	rightWorkingCopy = rightWorkingCopyPointer.data();
	rightWorkingCopy->getContent()->append (startText);

	leftSync = QSharedPointer<SyncThreadSub> (new SyncThreadSub(this, leftWorkingCopyPointer));
	rightSync = QSharedPointer<SyncThreadSub> (new SyncThreadSub(this, rightWorkingCopyPointer));

	leftShadowCopy = leftSync->getShadowCopy();
	rightShadowCopy = rightSync->getShadowCopy();

	leftEditList = leftSync->getEditList ();
	rightEditList = rightSync->getEditList ();
}

void SyncThreadTests::breakDownVariables()
{
	leftWorkingCopy = NULL;
	rightWorkingCopy = NULL;
	leftShadowCopy = NULL;
	rightShadowCopy = NULL;
	leftEditList = NULL;
	rightEditList = NULL;
}
