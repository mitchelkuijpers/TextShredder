#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField)
{
	//WorkingCopy * fileContents = file.data()->getWorkingCopy();

	//ui->textEditorField->setText(*fileContents->getContent());
    ui->setupUi(this);
}

SyncableFileTextField::~SyncableFileTextField()
{
    delete ui;
}
