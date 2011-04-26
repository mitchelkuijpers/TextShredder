#include "workingcopy.h"

WorkingCopy::WorkingCopy(QObject *parent) :
	Patchable(parent)
{
	lastEditDate = QDateTime::currentDateTime();
}

void WorkingCopy::applyPatches(QList<Patch> patches)
{
	Patchable::applyPatches(patches);
	lastEditDate = QDateTime::currentDateTime();
}

void WorkingCopy::setContent(QString &content) {
	Patchable::setContent(content);
	lastEditDate = QDateTime::currentDateTime();
}
