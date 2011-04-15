#ifndef PATCHABLE_H
#define PATCHABLE_H

#include <QObject>
//#include "diff_match_patch.h"

class Patchable : public QObject
{
    Q_OBJECT
public:
    Patchable(QObject *parent);
//    void applyPatches(QList<Patch> * patches);
//    QList<Patch> * getPatchesToConvertString(QString * otherString);
    QString * getContent();

protected:
    QString * content;

private:
//    diff_match_patch * dmpAlgorithm;

signals:

public slots:

};

#endif // PATCHABLE_H
