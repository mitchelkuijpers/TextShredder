#ifndef EDITLIST_H
#define EDITLIST_H

#include <QObject>
#include <QList>
#include <QMutex>
#include "edit.h"
#include "../../network/models/textshredderpacket.h"

class EditList : public QObject, public QMutex
{
	Q_OBJECT
public:
	/**
	  * Constructor which makes an EditList with or without a remote version.
	  *
	  * @param parent The parent object.
	  * @param remoteVersion The remoteVersion which will be used. Default is 0.
	  */
	EditList( QObject *parent, int remoteVersion = 0 );

	/**
	  * Copy constructor.
	  * The list of Edits and the remoteVersion will be copied.
	  *
	  * @param other The EditList object which will be copied.
	  */
	EditList( const EditList & other);

	/**
	  * Operator overload for the = operator.
	  * The list of Edits and the remoteVersion will be assigned.
	  *
	  * @param other The EditList object which will be assigned.
	  *
	  * @return A reference to this object after the assignment.
	  */
	EditList & operator=(EditList & other );

	/**
	  * Operator overload for the == operator.
	  * Will compare the EditList objects on their remote version and lists of Edit objects.
	  *
	  * @param other The object which this EditList object is compared to.
	  *
	  * @return The result of the comparison. True if both EditList objects are equal.
	  */
	bool operator==( EditList & other );

	/**
	  * Method to check whetter the EditList does not contain any Edit objects.
	  *
	  * @return Returns true if there are no Edit object in the edits variable.
	  */
	bool isEmpty();

	/**
	  * Method will remove all the Edit objects from the edits variable.
	  */
	void empty();

	/**
	  * Function will add an Edit object to the edits in the EditList object.
	  *
	  * @param edit The Edit object that should be added to the list.
	  */
	void addEdit( const Edit & edit );

	/**
	  * Method will remove the edits up to a local version from the edits variable.
	  * These popped edits are put into a variable and returned by the function.
	  * If 5 is passed as variable. Edits with version 4 and below are popped.
	  *
	  * @param version The version till which the Edit objects should be popped.
	  *
	  * @return The list with popped Edit objects.
	  */
	QList<Edit> popEditsUpToLocalVersion(unsigned int version);

	/**
	  * Setter for the remoteVersion variable.
	  *
	  * @param newRemoteVersion The new remote version for the EditList object.
	  */
	void setRemoteVersion( unsigned int newRemoteVersion);

	/**
	  * Getter for the remoteVersion variable.
	  *
	  * @return The current remote version of the EditList object.
	  */
	unsigned int getRemoteVersion();

	/**
	  * Getter for the edits variable.
	  *
	  * @return The edits variable.
	  */
	QList<Edit> & getEdits();

private:
	/** The list of edits. */
	QList<Edit> edits;

	/**
	  * The remoteVersion of the object. Is used as an acknowledgement.
	  * This is the version on which edits are based on.
	  */
	int remoteVersion;

signals:
	void editListEmpty();
	void editListNotEmpty();
};

#endif // EDITLIST_H
