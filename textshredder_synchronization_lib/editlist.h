#ifndef EDITLIST_H
#define EDITLIST_H

#include <QObject>
#include <QList>
#include <QMutex>
#include "edit.h"
#include "textshredderpacket.h"

class EditList : public QObject
{
    Q_OBJECT
public:
	/**
	  * Constructor which makes an EditList with or withou a remote version.
	  *
	  * @param the remoteVersion which will be used.
	  */
    EditList(QObject *parent, int remoteVersion = 0);

	/**
	  * Constructor which makes an EditList with a TextShredderPacket object
	  *
	  * @param the remoteVersion which will be used.
	  */
	EditList(QObject *parent, TextShredderPacket &);


	bool operator==(EditList &);
	/**
	  * Check whetter EditList does not contain any Edit objects.
	  */
	bool isEmpty();

	/**
	  * Function will add an Edit object to the edits in the EditList object
	  */
	void addEdit( const Edit & );

	/**
	  * Function will update EditList to a given remote version. It will
	  * change the remote version and drops the unused edits.
	  *
	  * @param the remote version to update to.
	  * @param the local version to update to. Is used to drop the edits.
	  */
	void updateToRemoteAndLocalVersion( unsigned int, unsigned int );

	/**
	  * Function will return a packet with the EditList as content.
	  */
	TextShredderPacket * getAllocatedPacket();

	//Setters
	void setRemoteVersion(unsigned int);

	//Getters
	unsigned int getRemoteVersion();
	QList<Edit> & getEdits();

private:
	QList<Edit> edits;
    int remoteVersion;
    QMutex mutex;

signals:

public slots:

};

#endif // EDITLIST_H
