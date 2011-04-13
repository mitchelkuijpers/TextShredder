#include "editlist.h"

EditList::EditList(QObject *parent, int remoteVersion) :
    QObject(parent), remoteVersion(remoteVersion)
{
}

unsigned int EditList::getRemoteVersion()
{
    return remoteVersion;
}

void EditList::setRemoteVersion(unsigned int newRemoteVersion)
{
    remoteVersion = newRemoteVersion;
}
