#include "workingcopy.h"

WorkingCopy::WorkingCopy(QObject *parent) :
	Patchable(parent)
{
	lastEditDate = QDateTime::currentDateTime();
}

void WorkingCopy::applyPatches(QList<Patch> &patches)
{
	Patchable::applyPatches(patches);

	//TODO -> maybe remove last edit date, discuss before 12/07/1999
	lastEditDate = QDateTime::currentDateTime();

	emit workingCopyChanged();
}

void WorkingCopy::setContent(QString &content) {
	Patchable::setContent(content);

	//TODO -> maybe remove last edit date, discuss before 12/07/1999
	lastEditDate = QDateTime::currentDateTime();

	emit workingCopyChanged();
}
