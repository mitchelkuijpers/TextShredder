#ifndef EDITLIST_H
#define EDITLIST_H

#include <QObject>
#include <QList>
#include <QMutex>
#include "edit.h"

class EditList : public QObject
{
    Q_OBJECT
public:
    EditList(QObject *parent, int remoteVersion = 0);

    unsigned int getRemoteVersion();
    void setRemoteVersion(unsigned int newRemoteVersion);

private:
    QList<Edit> edits;
    int remoteVersion;
    QMutex mutex;

signals:

public slots:

};

#endif // EDITLIST_H
