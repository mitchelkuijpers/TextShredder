#ifndef WORKINGCOPY_H
#define WORKINGCOPY_H

#include <QObject>
#include <QMutex>
#include "patchable.h"

class WorkingCopy : public Patchable, public QMutex
{
	Q_OBJECT
public:

	/**
	  * Constructor for a WorkingCopy with a parent as parameter.
	  *
	  * @param parent The parent object.
	  */
    WorkingCopy(QObject *parent);


	using Patchable::applyPatches;

	/**
	  * Overloaded function from the Patchable super class that will emit the signal
	  * workingCopyChanged()
	  *
	  * @param patches The list that will be used to call the super function to apply the patches.
	  */
	void applyPatches(QList<Patch> &patches);

	using Patchable::setContent;

	/**
	  * Overloaded function from the Patchable super class that will emit the signal
	  * workingCopyChanged()
	  *
	  * @param content The new content for the WorkingCopy instance.
	  */
	void setContent(QString &content);

signals:
	/**
	  * Signal that will be emitted when the internal content of the WorkingCopy instance was changed.
	  */
	void workingCopyChanged();
};

#endif // WORKINGCOPY_H
