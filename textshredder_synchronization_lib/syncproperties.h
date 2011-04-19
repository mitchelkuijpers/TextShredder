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
	SyncProperties(QObject *parent);
	SyncProperties(QObject *parent, int socketDescriptor,
				   WorkingCopy * workingCopy);

	//Getters
	TextShredderSocket * getSocket();
	WorkingCopy * getWorkingCopy();
private:
	EditList * editList;
	WorkingCopy * workingCopy;
	Patch * patch;
	TextShredderSocket * textShredderSocket;
	ShadowCopy * shadowCopy;
signals:

public slots:

};

#endif // SYNCPROPERTIES_H
