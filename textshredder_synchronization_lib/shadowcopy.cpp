#include "shadowcopy.h"

ShadowCopy::ShadowCopy(QObject *parent) :
    QObject(parent), localVersion(0), remoteVersion(0)
{
}

