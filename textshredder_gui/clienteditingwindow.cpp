#include "clienteditingwindow.h"
#include "ui_clienteditingwindow.h"

ClientEditingWindow::ClientEditingWindow(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::ClientEditingWindow)
{
    ui->setupUi(this);
}

ClientEditingWindow::~ClientEditingWindow()
{
    delete ui;
}

