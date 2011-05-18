#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField)
{
    ui->setupUi(this);

	WorkingCopy * fileContents = file.data()->getWorkingCopy();
	ui->textEditorField->setText(QString(*fileContents->getContent()));
}

SyncableFileTextField::~SyncableFileTextField()
{
    delete ui;
}
