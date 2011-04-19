#include "syncproperties.h"

SyncProperties::SyncProperties(QObject *parent) :
    QObject(parent)
{
};

SyncProperties::SyncProperties(QObject *parent, int socketDescriptor,
			   WorkingCopy * workingCopy) :
	QObject(parent), workingCopy(workingCopy)
{
	textShredderSocket = new TextShredderSocket(this, socketDescriptor);
	editList = new EditList(this);
};

TextShredderSocket * SyncProperties::getSocket()
{
	return textShredderSocket;
}

WorkingCopy * SyncProperties::getWorkingCopy()
{
	return workingCopy;
}
