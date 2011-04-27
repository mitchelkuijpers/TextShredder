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
	qDebug() << patches.first().toString();
	results = dmpAlgorithm.patch_apply(patches, content);
	qDebug() << QString("Old Content = ") << content;
	qDebug() << results;
	content = results.first;
	qDebug() << QString("New Content = ") << content;
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
