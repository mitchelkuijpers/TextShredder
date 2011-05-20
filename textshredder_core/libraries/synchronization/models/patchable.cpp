#include "patchable.h"

Patchable::Patchable(QObject *parent) :
    QObject(parent)
{
}

Patchable::Patchable(QObject *parent, QString content):
    QObject(parent), content(content)
{
}

void Patchable::applyPatches(QList<Patch> &patches)
{
	QPair<QString, QVector<bool> > results;	
	results = dmpAlgorithm.patch_apply(patches, content);
	content = results.first;
}

QList<Patch> Patchable::getPatchesToConvertString(QString &otherString)
{
	try {
		QList<Patch> patches = dmpAlgorithm.patch_make((QString) content, otherString);
		return patches;
	} catch (QString exception) {
		qDebug() << exception;
	}
}

QString * Patchable::getContent()
{
	return &content;
}

void Patchable::setContent(QString &content){
	this->content = content;
}
