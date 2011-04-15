#include "patchable.h"

Patchable::Patchable(QObject *parent) :
    QObject(parent)
{
}

void Patchable::applyPatches(QList<Patch> *patches)
{

}

QList<Patch> * Patchable::getPatchesToConvertString(QString *otherString)
{
    return NULL;
}

QString * Patchable::getContent()
{
    return content;
}
