#ifndef PATCHABLE_H
#define PATCHABLE_H

#include <QObject>
#include "../textshredder_core/libraries/diff_match_patch/diff_match_patch.h"

class Patchable : public QObject
{
	Q_OBJECT

public:
	/**
	  * Constructor to create a Patchable object with only a parent.
	  *
	  * @param parent The parent object.
	  */
	Patchable(QObject *parent);

	/**
	  * Constructor to create a Patchable object with a parent and a content string.
	  *
	  * @param parent The parent object.
	  * @param content The content string for the patchable.
	  */
	Patchable(QObject *parent, QString content);

	/**
	  * Method to apply a list of Patch objects on the patchable content.
	  *
	  * @param patches The patches to apply.
	  */
	void applyPatches(QList<Patch> &patches);

	/**
	  * Method will return a list of patches to convert this Patchable instance content to the otherString value.
	  *
	  * @return The list of patches to convert this Patchable.
	  */
    QList<Patch> getPatchesToConvertString(QString &otherString);

	/**
	  * Method will return a pointer to the content string.
	  *
	  * @return The content pointer.
	  */
	QString * getContent();

	/**
	  * Will set the content of this Patchable object to a new content.
	  *
	  * @param content The new content the Patchable.
	  */
	void setContent( QString & content );

protected:
	/**
	  * The content string of the patchable.
	  */
	QString content;

	/**
	  * The diff_match_patch used to calculate the patches.
	  */
	diff_match_patch dmpAlgorithm;
};

#endif // PATCHABLE_H
