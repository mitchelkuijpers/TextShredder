#include "patchable.h"

Patchable::Patchable(QObject *parent) :
    QObject(parent)
{
}

Patchable::Patchable(QObject *parent, QString content):
    QObject(parent), content(content)
{
}

void Patchable::applyPatches(QList<Patch> patches)
{
	QPair<QString, QVector<bool> > results;
	results = dmpAlgorithm.patch_apply(patches, content);
	content = results.first;
}

QList<Patch> Patchable::getPatchesToConvertString(QString &otherString)
{
	return dmpAlgorithm.patch_make((QString) content, otherString);
}

QString * Patchable::getContent()
{
	return &content;
}

void Patchable::setContent(QString &content){
	this->content = content;
}
