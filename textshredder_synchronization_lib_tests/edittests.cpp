#include "edittests.h"


void EditTests::testCreateEmptyConstructor()
{
    Edit * testEdit = new Edit(this);
    QVERIFY2(testEdit != NULL, "Failed to create new Edit");
}

void EditTests::testCreateConstructorWithParameters()
{
    diff_match_patch dmp;
    int localVersion = 4;
    QList<Patch> patches = "@@ -0,0 +1,3 @@\n+abc\n";
    Edit * testEdit = new Edit(this, localVersion, patches);
    QVERIFY2(testEdit != NULL, "Failed to create new Edit with parameters");
    assertEquals(testEdit->getPatches(), "@@ -0,0 +1,3 @@\n+abc\n");
    assertEquals(testEdit->getLocalVersion(), 4);

}
