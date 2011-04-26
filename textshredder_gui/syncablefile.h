#ifndef SYNCABLEFILE_H
#define SYNCABLEFILE_H

#include <QObject>

class SyncableFile : public QObject
{
    Q_OBJECT
public:
    explicit SyncableFile(QObject *parent = 0);

signals:

public slots:

};

#endif // SYNCABLEFILE_H
