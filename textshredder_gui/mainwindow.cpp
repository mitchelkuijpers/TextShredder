#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	connect(ui->serverTab, SIGNAL(serverStarted()), this, SLOT(serverDidStart()));
	ui->main_tab_widget->setCurrentWidget(ui->serverTab);
	ui->main_tab_widget->setTabEnabled(2, false);
	connect(ui->clientTab, SIGNAL(connectedToHost(int)), this, SLOT(clientConnected(int)));
	connect(ui->clientEditingTab, SIGNAL(clientDisconnected()), this, SLOT(clientDisconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverDidStart()
{
	ui->main_tab_widget->setCurrentWidget(ui->clientEditingTab);
	ui->main_tab_widget->setTabEnabled(0, false);
	ui->main_tab_widget->setTabEnabled(1, false);
	ui->main_tab_widget->setTabEnabled(2, true);
	ui->clientEditingTab->setWorkingCopy(ui->serverTab->getWorkingCopy());
}

void MainWindow::clientDisconnected()
{
	ui->main_tab_widget->setCurrentWidget(ui->clientTab);
	ui->main_tab_widget->setTabEnabled(0, true);
	ui->main_tab_widget->setTabEnabled(1, true);
	ui->main_tab_widget->setTabEnabled(2, false);
}

void MainWindow::clientConnected(int socketDescriptor)
{
	ui->main_tab_widget->setCurrentWidget(ui->clientEditingTab);
	ui->main_tab_widget->setTabEnabled(0, false);
	ui->main_tab_widget->setTabEnabled(1, false);
	ui->main_tab_widget->setTabEnabled(2, true);
	ui->clientEditingTab->startWithSocketDescriptor(socketDescriptor);
}
