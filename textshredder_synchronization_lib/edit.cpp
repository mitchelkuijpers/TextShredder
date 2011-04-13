#include "edit.h"

Edit::Edit(QObject *parent) :
    QObject(parent), localVersion(0)
{
}

unsigned int Edit::getLocalVersion()
{
    return localVersion;
}

void Edit::setLocalVersion(unsigned int newLocalVersion)
{
    localVersion = newLocalVersion;
}
