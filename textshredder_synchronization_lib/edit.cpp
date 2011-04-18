#include "edit.h"

Edit::Edit(QObject *parent) :
    QObject(parent), localVersion(0), patches(NULL)
{
}

Edit::Edit(const Edit &copy) : QObject(copy.parent())
{
	this->localVersion = copy.localVersion;
	this->patches = copy.patches;
}

Edit::Edit(QObject *parent, unsigned int localVersion, QList<Patch> *patches) :
        QObject(parent), localVersion(localVersion), patches(patches)
{
}

Edit& Edit::operator = (const Edit& other)
{
	this->localVersion = other.localVersion;
	this->patches = other.patches;
	return *this;
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
