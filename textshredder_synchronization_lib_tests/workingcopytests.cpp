#include "workingcopytests.h"

void WorkingCopyTests::testHello()
{
    int i = 1;
    int x = 1;

    QVERIFY2(i == x, "I isn't equal to X");
}

