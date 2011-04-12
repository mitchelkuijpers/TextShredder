#include "servertabwindow.h"
#include "ui_servertabwindow.h"

ServerTabWindow::ServerTabWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerTabWindow)
{
    ui->setupUi(this);
}

ServerTabWindow::~ServerTabWindow()
{
    delete ui;
}
