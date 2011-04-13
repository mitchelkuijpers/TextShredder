#include "clientactivewindow.h"
#include "ui_clientactivewindow.h"

ClientActiveWindow::ClientActiveWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientActiveWindow)
{
    ui->setupUi(this);
}

ClientActiveWindow::~ClientActiveWindow()
{
    delete ui;
}

