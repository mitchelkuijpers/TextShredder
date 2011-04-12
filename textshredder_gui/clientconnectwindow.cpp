#include "clientconnectwindow.h"
#include "ui_clientconnectwindow.h"

ClientConnectWindow::ClientConnectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientConnectWindow)
{
    ui->setupUi(this);
}

ClientConnectWindow::~ClientConnectWindow()
{
    delete ui;
}

