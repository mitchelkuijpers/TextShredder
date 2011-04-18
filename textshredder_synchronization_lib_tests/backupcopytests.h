#ifndef BACKUPCOPYTESTS_H
#define BACKUPCOPYTESTS_H

#include <QtCore/QString>
#include "autotest.h"

class BackupCopyTests: public QObject
{
    Q_OBJECT

private:


private Q_SLOTS:
        void createBackupCopyWithDefaultLocalVersionNumber();
        void createBackupCopyWithGivenLocalVersionNumber();
};

DECLARE_TEST(BackupCopyTests);

#endif // BACKUPCOPYTESTS_H
