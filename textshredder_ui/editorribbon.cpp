#include "editorribbon.h"
#include "ui_editorribbon.h"

EditorRibbon::EditorRibbon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorRibbon)
{
    ui->setupUi(this);

	ui->horizontalLine->setFrameShape(QFrame::HLine);
	ui->horizontalLine->setFrameShadow(QFrame::Sunken);

	ui->verticalLine->setFrameShape(QFrame::VLine);
	ui->verticalLine->setFrameShadow(QFrame::Sunken);
}

EditorRibbon::~EditorRibbon()
{
    delete ui;
}
