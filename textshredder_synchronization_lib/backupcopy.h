#ifndef BACKUPCOPY_H
#define BACKUPCOPY_H

#include <QObject>

class BackupCopy : public QObject
{
    Q_OBJECT
public:
    explicit BackupCopy(QObject *parent);

signals:

public slots:

private:
    int localVersion;
    QString * fileContent;
};

#endif // BACKUPCOPY_H
