#ifndef EDIT_H
#define EDIT_H

#include <QObject>
#include "../textshredder_diff_match_patch/diff_match_patch.h"

class Edit : public QObject
{
    Q_OBJECT
public:
    /**
      * Create new Edit without parameters
      */
    Edit(QObject *parent);
    /**
      * Create new Edit with a localVersion and patches given
      * @param localVersion of the Edit
      * @param patches of the Edit
      */
    Edit(QObject *parent, unsigned int localVersion, QList<Patch> * patches);

    unsigned int getLocalVersion();
    QList<Patch> * getPatches();

    void setLocalVersion(unsigned int newLocalVersion);
    void setPatches(QList<Patch> * newPatches);



signals:

public slots:

private:
    unsigned int localVersion;
    QList<Patch> * patches;


};

#endif // EDIT_H
