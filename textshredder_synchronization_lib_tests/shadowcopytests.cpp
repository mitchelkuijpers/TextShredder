#include "shadowcopytests.h"



void ShadowCopyTests::applyEditsTest()
{
	/*ShadowCopy *shadowCopyTest = new ShadowCopy(this);
	QList<Edit> editList;
	QList<Patch> patches;
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString expectedPatch = "@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n";

	// The second patch must be "-21,17 +21,18", not "-22,17 +21,18" due to rolling context.
	//patches = dmp->patch_make(text2, text1);
	editList[0] = new Edit(this, 0, &patches);
	shadowCopyTest->applyEdits();*/
}


void ShadowCopyTests::revertTest()
{
	/*ShadowCopy *shadowCopyTest = new ShadowCopy(this);
	shadowCopyTest->applyEdits();
	shadowCopyTest->revert();*/

}

void ShadowCopyTests::backupTest()
{
	/*ShadowCopy *shadowCopyTest = new ShadowCopy(this);
	shadowCopyTest->backup();*/

}

void ShadowCopyTests::processPatchesTest()
{
	/*ShadowCopy *shadowCopyTest = new ShadowCopy(this);
	shadowCopyTest->processPatches();*/
}
