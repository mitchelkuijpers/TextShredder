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
        QVERIFY2(leftShadowCopy->getLocalVersion() == 1, "leftShadowCopy localversion is not 1");
        QVERIFY2(leftShadowCopy->getContent() == leftWorkingCopy->getContent(),
                 "ShadowCopy content is not equal to WorkingCopyContent");

	//validate leftBackup //localVersion =0 / text is beforeText;
        QVERIFY2(leftShadowCopy->getBackupCopy()->getLocalVersion() == 0,
                 "BackupVersion != 0");
        QVERIFY2(leftShadowCopy->getBackupCopy()->getContent() == beforeText,
                 "BackupCopy content != beforeText");

        //validate leftEditList //Based version = 0, contains 1 edit. First edit local version = 1
        QVERIFY2(leftEditList->getRemoteVersion() == 0,
                 "LeftEditList version != 0");
        QVERIFY2(leftEditList->getEdits().size() == 1,
                 "LeftEditList != contains 1 edit");
        QVERIFY2(leftEditList->getEdits().first().getLocalVersion() == 1,
                 "First edit local version != 1");

        //optional test patch in edit.

	//validate rightShadow.content == leftSh.content. rithSH.rem = 1, loc =0
        QVERIFY2(rightShadowCopy->getContent() == leftShadowCopy->getContent(),
                "rightshadowcopy content != leftshadowcopy content");
        QVERIFY2(rightShadowCopy->getRemoteVersion() == 1,
                 "rightshadowcopy remoteVersion != 1");
        QVERIFY2(rightShadowCopy->getLocalVersion() == 0,
                 "rightshadowcopy localversion != 0");

	//validate rightShadow.con == rightBackup.content
        QVERIFY2(rightShadowCopy->getContent() == rightShadowCopy->getBackupCopy()->getContent(),
                 "rightshadow content != rightbackup content");

        //validate rightBU.loc = 0;
        QVERIFY2(rightShadowCopy->getBackupCopy()->getLocalVersion() == 0,
                 "backupcopy localversion != 0");

        //validate rightWC.con == righSh.con
        QVERIFY2(rightWorkingCopy->getContent() == rightShadowCopy->getContent(),
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

        QVERIFY2(leftShadowCopy->getLocalVersion() == 1,
                 "leftshadowcopy localversion != 1");
        QVERIFY2(leftShadowCopy->getContent() == leftWorkingCopy->getContent(),
                 "leftshadowcopy content != leftWorkingcopy content");

	//validate leftBackup //localVersion = 1 / text is leftSH.con;
        QVERIFY2(leftShadowCopy->getBackupCopy()->getLocalVersion() ==1,
                 "backupcopy localversion != 1");
        QVERIFY2(leftShadowCopy->getBackupCopy()->getContent() == leftShadowCopy->getContent(),
                 "leftbackupcopy content != shadowcopy content");

	//validate leftEditList //Based version = 0, contains 0 edits.  count = 0
        QVERIFY2(leftEditList->getRemoteVersion() == 0,
                 "leftEditList remoteversion != 0");
        QVERIFY2(leftEditList->isEmpty(),
                 "left editlist != empty");

	breakDownVariables();
}


void SyncThreadTests::pushChangesTest()
{
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
