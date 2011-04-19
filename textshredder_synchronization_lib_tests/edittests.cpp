#include "edittests.h"

#include <QtCore>
#include "../textshredder_diff_match_patch/diff_match_patch.h"


void EditTests::testCreateEmptyConstructor()
{
	Edit * testEdit = new Edit(this);
	QVERIFY2(testEdit != NULL, "Failed to create new Edit");
}

void EditTests::testCreateConstructorWithParameters()
{
	diff_match_patch *dmp = new diff_match_patch();

	unsigned int localVersion = 4;
	QList<Patch> patches;
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString expectedPatch = "@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n";

	// The second patch must be "-21,17 +21,18", not "-22,17 +21,18" due to rolling context.
	patches = dmp->patch_make(text2, text1);

	Edit * testEdit = new Edit(this, localVersion, patches);
	QVERIFY2(testEdit != NULL, "Failed to create new Edit with parameters");

	QVERIFY2(testEdit->getLocalVersion() == localVersion, "LocalVersion does not match");
	QVERIFY2(QString::compare(testEdit->getPatches().first().toString(), expectedPatch) != 0, "Invalid patch");

	delete dmp;
}
