#ifndef SYNCABLEFILETEXTFIELD_H
#define SYNCABLEFILETEXTFIELD_H

#include <QWidget>
#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"

namespace Ui {
	class SyncableFileTextField;
}

class SyncableFileTextField : public QWidget
{
    Q_OBJECT

public:
	SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file);
	~SyncableFileTextField();

private:
	Ui::SyncableFileTextField *ui;
};

#endif // TEXTFIELD_H
