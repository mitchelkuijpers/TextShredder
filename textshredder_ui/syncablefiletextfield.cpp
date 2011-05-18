#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"

SyncableFileTextField::SyncableFileTextField(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField)
{
    ui->setupUi(this);
}

SyncableFileTextField::~SyncableFileTextField()
{
    delete ui;
}
