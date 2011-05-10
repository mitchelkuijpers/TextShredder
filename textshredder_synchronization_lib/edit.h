#ifndef EDIT_H
#define EDIT_H

#include <QObject>
#include "../textshredder_diff_match_patch/diff_match_patch.h"

class Edit : public QObject
{
    Q_OBJECT
public:
    /**
      * Create new Edit without parameters
      */
    Edit(QObject *parent);

	/**
	  * Create new Edit with a localVersion and patches given
	  * @param localVersion of the Edit
	  * @param patches of the Edit
	  */
	Edit(QObject *parent, unsigned int localVersion, QList<Patch> & patches);

	/**
	  * Constructor to make Edit from bytes. Normally used to send an edit
	  * for synchronization, but can also be used for persistence.
	  *
	  * @param the bytes used to make the edit.
	  */
	Edit(QObject *, QByteArray &);

	/**
	  * Copy constructor.
	  */
	Edit(const Edit &copy);

	/**
	  * Overloaded the assign operator.
	  */
	Edit& operator = (const Edit&);

	/**
	  * Overloaded the equals operator.
	  */
	bool operator == (const Edit&);

	/**
	  * Will append the string reprentation to a QByteArray
	  */
	void appendEditBytesToByteArray(QByteArray &bytesArray);

	//Setters
	void setLocalVersion(unsigned int newLocalVersion);
	void setPatches(QList<Patch> & newPatches);

	//Getters
	unsigned int getLocalVersion();
	QList<Patch> & getPatches();

	QString toString();
signals:

public slots:

private:
    unsigned int localVersion;
	QList<Patch> patches;


};

#endif // EDIT_H
