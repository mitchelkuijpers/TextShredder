#ifndef EDITLIST_H
#define EDITLIST_H

#include <QObject>
#include <QList>
#include <QMutex>
#include "edit.h"
#include "textshredderpacket.h"

class EditList : public QObject, public QMutex
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
	  * Constructor which makes an EditList with QByteArray
	  *
	  * @param the remoteVersion which will be used.
	  */
	EditList(QObject *parent, QByteArray &content);
	/**
	  * Constructor which makes an EditList with a TextShredderPacket object
	  *
	  * @param the remoteVersion which will be used.
	  */
	EditList(QObject *parent, TextShredderPacket &);

	EditList(const EditList &);
	EditList & operator=(EditList &);
	bool operator==(EditList &);

	/**
	  * Check whetter EditList does not contain any Edit objects.
	  */
	bool isEmpty();

	/**
	  * Empty the edit list.
	  */
	void empty();

	/**
	  * Function will add an Edit object to the edits in the EditList object
	  */
	void addEdit( const Edit & );

	/**
	  * Function will update EditList to a given remote version.
	  *
	  * @param the remote version to update to.
	  */
	void updateToRemote(	unsigned int newRemoteVersion);

	/**
	  * Function will return a packet with the EditList as content.
	  */
	TextShredderPacket * getAllocatedPacket();

	//Setters
	void setRemoteVersion(unsigned int);

	//Getters
	unsigned int getRemoteVersion();
	QList<Edit> & getEdits();
	QList<Edit> popEditsUpToLocalVersion(unsigned int version);
private:
	QList<Edit> edits;
    int remoteVersion;
    QMutex mutex;

signals:

public slots:

};

#endif // EDITLIST_H
