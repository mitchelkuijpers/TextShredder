#include "shadowcopy.h"
#include "editlist.h"

ShadowCopy::ShadowCopy(QObject *parent, int localVersion) :
        QObject(parent), localVersion(localVersion), remoteVersion(0)
{
}

int ShadowCopy::getLocalVersion()
{
    return 0;
}

void ShadowCopy::revert()
{

}

void ShadowCopy::backup()
{

}

//void ShadowCopy::applyEdits( QList<Edit> * edits )
//{

//}

int ShadowCopy::getRemoteVersion()
{
    return 0;
}

//void ShadowCopy::processPatches( QList<Patch> * patches)
//{

//}
