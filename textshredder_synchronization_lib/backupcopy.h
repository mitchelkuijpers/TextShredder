#ifndef BACKUPCOPY_H
#define BACKUPCOPY_H

#include <QObject>

class BackupCopy : public QObject
{
    Q_OBJECT

public:
    BackupCopy( QObject *parent, QString & content );
    BackupCopy( QObject *parent, QString & content, int localVersion );
    int getLocalVersion();
    QString * getContent();

signals:

public slots:

private:
    int localVersion;
    QString * content;
};

#endif // BACKUPCOPY_H
