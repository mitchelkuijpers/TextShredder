#include "shadowcopy.h"
#include "editlist.h"

ShadowCopy::ShadowCopy(QObject *parent, QString & content, int localVersion ) :
    QObject(parent), localVersion(localVersion), remoteVersion(0)
{
}


void ShadowCopy::lock()
{

}

void ShadowCopy::unlock()
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

void ShadowCopy::applyEdits( QList<Edit> * edits )
{

}

int ShadowCopy::getRemoteVersion()
{
    return 0;
}

QString * ShadowCopy::getContent()
{

}

void ShadowCopy::processPatches( QList<Patch> * patches)
{

}
