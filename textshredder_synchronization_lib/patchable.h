#ifndef PATCHABLE_H
#define PATCHABLE_H

#include <QObject>
#include "../textshredder_diff_match_patch/diff_match_patch.h"

class Patchable : public QObject
{
    Q_OBJECT
public:
    Patchable(QObject *parent);
    Patchable(QObject *parent, QString * content);

	void applyPatches(QList<Patch> patches);
    QList<Patch> getPatchesToConvertString(QString &otherString);
    QString * getContent();

protected:
	QString * content;

private:
	diff_match_patch dmpAlgorithm;

signals:

public slots:

};

#endif // PATCHABLE_H
