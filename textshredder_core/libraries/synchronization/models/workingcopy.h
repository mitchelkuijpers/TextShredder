#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

#include <QObject>
#include <QMutex>
#include "patchable.h"

class WorkingCopy : public Patchable, public QMutex
{
	Q_OBJECT
public:
    WorkingCopy(QObject *parent);

	using Patchable::applyPatches;
	void applyPatches(QList<Patch> &patches);

	using Patchable::setContent;
	void setContent(QString &content);

signals:
	void workingCopyChanged();

public slots:

private:
	QDateTime lastEditDate;

};

#endif // WORKINGCOPY_H
