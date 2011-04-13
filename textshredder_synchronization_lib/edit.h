#ifndef EDIT_H
#define EDIT_H

#include <QObject>
#include "../textshredder_diff_match_patch/diff_match_patch.h"

class Edit : public QObject
{
    Q_OBJECT
public:
    Edit(QObject *parent);
    unsigned int getLocalVersion();
    void setLocalVersion(unsigned int newLocalVersion);

private:
    QList<Patch> * patches;
    unsigned int localVersion;

signals:

public slots:

};

#endif // EDIT_H
