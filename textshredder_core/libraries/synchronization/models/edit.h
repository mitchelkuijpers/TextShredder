#ifndef EDIT_H
#define EDIT_H

#include <QObject>
#include "../../diff_match_patch/diff_match_patch.h"

class Edit : public QObject
{
    Q_OBJECT
public:
	/**
	  * Constructor which creates  a new Edit without parameters.
	  *
	  * @param parent The parent object.
	  */
	Edit( QObject *parent );

	/**
	  * Constructor which creates  new Edit with a localVersion and given patches.
	  *
	  * @param localVersion The localVersion of the Edit.
	  * @param patches The patches the Edit will hold.
	  */
	Edit( QObject *parent, unsigned int localVersion, QList<Patch> & patches );

	/**
	  * Constructor to make Edit from bytes. Normally used to send an edit
	  * for synchronization, but can also be used for persistence.
	  *
	  * @param the bytes used to make the edit.
	  */
	Edit( QObject *parent, QByteArray & byteRepresentation );

	/**
	  * Copy constructor.
	  *
	  * @param copy The edit which will be copied. The local version and the edits will be copied.
	  */
	Edit( const Edit &copy );

	/**
	  * Operator overload for the = operator.
	  * The local version and the edits will be assigned.
	  *
	  * @param other The object to which this Edit object gets assigned to.
	  *
	  * @return A reference to this object that has been assigned to the other parameter.
	  */
	Edit & operator=( const Edit & other );

	/**
	  * Operator overload for the == operator.
	  * The Edit object will be compared to the other Edit object.
	  * The comparison will be on the localVersion and on the list off patches.
	  *
	  * @param other The object this object is being compared to.
	  *
	  * @return A boolean value if both object are equal. Returns true if so.
	  */
	bool operator==( const Edit & other );

	/**
	  * Method will append the byte representation of this Edit object to the QByteArray passed as parameter.
	  *
	  * @param bytesArray The QByteArray in which this Edit object is stored.
	  */
	void appendEditBytesToByteArray(QByteArray &bytesArray);

	/**
	  * Method will set the local version of this Edit to a new local version.
	  *
	  * @param newLocalVerion The new local version for the Edit.
	  */
	void setLocalVersion(unsigned int newLocalVersion);

	/**
	  * Method will set the list of patches for the Edit object to the given parameter.
	  *
	  * @param newLocalVerion The new local version for the Edit.
	  */
	void setPatches(QList<Patch> & newPatches);

	/**
	  * Method will return the local version of this Edit object.
	  *
	  * @return The current local version.
	  */
	unsigned int getLocalVersion();

	/**
	  * Method will return the patches stored in the Edit object.
	  *
	  * @return The current patches stored in the edit.
	  */
	QList<Patch> & getPatches();

private:
	/**
	  * The local version of the Edit object.
	  */
	unsigned int localVersion;

	/**
	  * The list of patches stored in the Edit object.
	  */
	QList<Patch> patches;

};

#endif // EDIT_H
