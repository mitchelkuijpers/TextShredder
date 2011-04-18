#include "shadowcopy.h"
#include "editlist.h"


ShadowCopy::ShadowCopy(QObject *parent) :
		Patchable(parent), localVersion(0), remoteVersion(0)
{
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



void ShadowCopy::processPatches( QList<Patch> * patches)
{

}

int ShadowCopy::getRemoteVersion()
{
	return remoteVersion;
}

int ShadowCopy::getLocalVersion()
{
	return localVersion;
}
