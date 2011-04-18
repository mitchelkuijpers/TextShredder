#include "patchabletests.h"
#include "../textshredder_diff_match_patch/diff_match_patch.h"

void PatchableTests::testGetContent() {
    QString content = "TestStringContent";
    Patchable * newPatchable = NULL;
    newPatchable = new Patchable(this, &content);

    QVERIFY2(newPatchable->getContent() == content, "Unable to retrieve content");
}

void PatchableTests::testGetPatchesToConvertString() {
	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString expectedPatch = "@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n";
    QList<Patch> patches;

	diff_match_patch dmpAlgorithm;

	Patchable * newPatchable = NULL;
	newPatchable = new Patchable(this, &text1);
	patches = newPatchable->getPatchesToConvertString(text2);

	QVERIFY2(QString::compare(dmpAlgorithm.patch_toText(patches), expectedPatch) != 0, "Not the same" );

 }

void PatchableTests::testApplyPatches() {

	QString text1 = "The quick brown fox jumps over the lazy dog.";
	QString text2 = "That quick brown fox jumped over a lazy dog.";
	QString patchText = "@@ -1,8 +1,7 @@\n Th\n-at\n+e\n  qui\n@@ -21,17 +21,18 @@\n jump\n-ed\n+s\n  over \n-a\n+the\n  laz\n";
	QList<Patch> patches;

	diff_match_patch dmpAlgorithm;

	Patchable * newPatchable = NULL;
	newPatchable = new Patchable(this, &text2);

	patches = dmpAlgorithm.patch_fromText(patchText);
	newPatchable->applyPatches(patches);

	QVERIFY2(QString::compare(*newPatchable->getContent(), text1) == 0, "Not patched right" );
}
