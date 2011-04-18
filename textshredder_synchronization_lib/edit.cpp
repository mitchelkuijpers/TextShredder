#include "edit.h"

Edit::Edit(QObject *parent) :
    QObject(parent), localVersion(0)
{
}

Edit::Edit(QObject *parent, unsigned int localVersion, QList<Patch> *patches) :
        QObject(parent)
{
   this->localVersion = localVersion;
   this->patches = patches;
}

unsigned int Edit::getLocalVersion()
{
    return localVersion;
}

QList<Patch> * Edit::getPatches()
{
    return patches;
}


void Edit::setLocalVersion(unsigned int newLocalVersion)
{
    localVersion = newLocalVersion;
}

void Edit::setPatches(QList<Patch> *newPatches)
{
    this->patches = newPatches;
}
