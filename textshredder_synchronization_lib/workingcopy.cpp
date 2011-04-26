#include "workingcopy.h"

WorkingCopy::WorkingCopy(QObject *parent) :
	Patchable(parent)
{
}

void WorkingCopy::applyPatches(QList<Patch> patches)
{
	Patchable::applyPatches(patches);
}
