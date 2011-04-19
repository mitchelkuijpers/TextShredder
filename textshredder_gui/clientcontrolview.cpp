#include "clientcontrolview.h"
#include "ui_clientcontrolview.h"

ClientControlView::ClientControlView(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::ClientControlView)
{
    ui->setupUi(this);
}

ClientControlView::~ClientControlView()
{
    delete ui;
}

