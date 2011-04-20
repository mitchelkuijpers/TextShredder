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

	SyncProperties(QObject *parent, int socketDescriptor,
				   WorkingCopy * workingCopy);


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
