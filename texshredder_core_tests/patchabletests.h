#ifndef PATCHABLETESTS_H
#define PATCHABLETESTS_H

#include <QtCore/QString>
#include "../textshredder_synchronization_lib/patchable.h"
#include "autotest.h"


class PatchableTests: public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testGetContent();
    void testGetPatchesToConvertString();
    void testApplyPatches();
};

DECLARE_TEST(PatchableTests);

#endif // PATCHABLETESTS_H
