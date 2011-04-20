#ifndef SYNCPROPERTIES_H
#define SYNCPROPERTIES_H

#include <QObject>
#include "../textshredder_diff_match_patch/diff_match_patch.h"
#include "editlist.h"
#include "workingcopy.h"
#include "textshreddersocket.h"
#include "shadowcopy.h"

class SyncProperties : public QObject
{
    Q_OBJECT

public:

	/**
	  * Constructor for SyncProperties. It will initialize the class
	  * properties with the given parameters.
	  *
	  * @param the parent object.
	  * @param the socket desriptor used to sync with.
	  * @param the working copy reference.
	  */
	SyncProperties(QObject *parent, int socketDescriptor,
				   WorkingCopy * workingCopy);

	/**
	  * Function to apply an received edit list on the Shadow and Working copy.
	  *
	  * @param the edit list to apply.
	  */
	void applyReceivedEditList(EditList &editList);

	//Getters
	TextShredderSocket * getSocket();
	WorkingCopy * getWorkingCopy();

private:
	WorkingCopy * workingCopy;
	EditList editList;
	TextShredderSocket textShredderSocket;
	ShadowCopy shadowCopy;
signals:

public slots:
	void pushChanges();
	void processChanges();
};

#endif // SYNCPROPERTIES_H
