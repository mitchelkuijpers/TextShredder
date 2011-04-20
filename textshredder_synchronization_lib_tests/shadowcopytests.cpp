#include "shadowcopytests.h"

void ShadowCopyTests::revertTest()
{
	QString text1 = "HALLLO";
	QString text2 = "hallow";
	ShadowCopy * testShadow;
	testShadow = new ShadowCopy(this, text1);
	testShadow->setContent(text2);
	testShadow->revert();
	QVERIFY2(QString::compare(*(testShadow->getContent()), text1) == 0, "Revert failed");
	QVERIFY2(testShadow->getLocalVersion() == testShadow->getBackupCopy()->getLocalVersion(),
			 "LocalVersion has not been reversed");

}

void ShadowCopyTests::backupTest()
{
	QString text1 = "ABC";
	QString text2 = "XYZ";
	ShadowCopy * testShadow;
	testShadow = new ShadowCopy(this, text1);
	testShadow->getBackupCopy()->setContent(text2);
	testShadow->backup();
	QVERIFY2(QString::compare(*(testShadow->getBackupCopy()->getContent()), text1) == 0, "Backup failed");
	QVERIFY2(testShadow->getLocalVersion() == testShadow->getBackupCopy()->getLocalVersion(),
			 "backupversion has not been updated");
}

void ShadowCopyTests::applyEditsTestWithOnePatch()
{
	unsigned int oldRemoteVersion;
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString s1("@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n");

	ShadowCopy * testShadow;
	//create testShadowCopy with text2 as content
	testShadow = new ShadowCopy(this, text2);

	oldRemoteVersion = testShadow->getRemoteVersion();
	QList<Edit> testEdits;
	diff_match_patch dmp;


	QList<Patch> pList1 = dmp.patch_fromText(s1);

	Edit e1(this, 1, pList1);

	testEdits.insert(0, e1);


	testShadow->applyEdits(testEdits);

	QVERIFY2(QString::compare(*(testShadow->getContent()), text1) == 0,
			 "Shadow did not patch");
	QVERIFY2(testShadow->getRemoteVersion() == oldRemoteVersion+1,
			 "Didn't update remote version correctly");
}

void ShadowCopyTests::applyEditsTestWithMultiplePatches()
{
	unsigned int oldRemoteVersion;
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString s1("@@ -1,8 +1,7 @@\n Th\n-at\n+xb\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+f\n  over\n");
	QString s2("@@ -1,8 +1,7 @@\n Th\n-xb\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-f\n+s\n  over \n-a\n+the\n  laz\n");

	ShadowCopy * testShadow;
	//create testShadowCopy with text2 as content
	testShadow = new ShadowCopy(this, text2);

	oldRemoteVersion = testShadow->getRemoteVersion();
	QList<Edit> testEdits;
	diff_match_patch dmp;


	QList<Patch> pList1 = dmp.patch_fromText(s1);
	QList<Patch> pList2 = dmp.patch_fromText(s2);

	Edit e1(this, 1, pList1);
	Edit e2(this, 2, pList2);
	testEdits.insert(0, e1);
	testEdits.insert(1, e2);

	testShadow->applyEdits(testEdits);
	QVERIFY2(QString::compare(*(testShadow->getContent()), text1) == 0,
			 "Shadow did not patch");
	QVERIFY2(testShadow->getRemoteVersion() == oldRemoteVersion+2, "Didnt patch twice");
}

void ShadowCopyTests::applyEditsTestWhenAlreadyUpToDate()
{
	unsigned int oldRemoteVersion;
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString s1("@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n");
	QString s2("@@ -1,8 +1,7 @@\n Th\n-xb\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-f\n+s\n  over \n-a\n+the\n  laz\n");

	ShadowCopy * testShadow;
	//create testShadowCopy with text2 as content
	testShadow = new ShadowCopy(this, text2);

	oldRemoteVersion = testShadow->getRemoteVersion();
	QList<Edit> testEdits;
	diff_match_patch dmp;


	QList<Patch> pList1 = dmp.patch_fromText(s1);
	QList<Patch> pList2 = dmp.patch_fromText(s2);

	Edit e1(this, 1, pList1);
	Edit e2(this, 0, pList2);
	testEdits.insert(0, e1);
	testEdits.insert(1, e2);

	testShadow->applyEdits(testEdits);

	QVERIFY2(QString::compare(*(testShadow->getContent()), text1) == 0,
			 "Shadow did not patch");
	QVERIFY2(testShadow->getRemoteVersion() == oldRemoteVersion+1,
			 "Didn't update remote version correctly");

}


void ShadowCopyTests::processPatchesTest()
{
	unsigned int oldVersionNumber;
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString s("@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n");
	ShadowCopy * testShadow;
	testShadow = new ShadowCopy(this, text2);
	oldVersionNumber = testShadow->getLocalVersion();

	QList<Edit> testEdits;
	diff_match_patch dmp;


	QList<Patch> pList1 = dmp.patch_fromText(s);
	QList<Patch> pList2 = dmp.patch_fromText(s);

	Edit e1(this, 400, pList1);
	Edit e2(this, 255, pList2);
	testEdits.insert(0, e1);
	testEdits.insert(1, e2);

	testShadow->processPatches(&pList1);

	QVERIFY2(QString::compare(*(testShadow->getContent()), text1) == 0,
			 "Shadow did not patch");
	QVERIFY2(testShadow->getLocalVersion() == oldVersionNumber+1,
			 "Version number didn't update");
}
