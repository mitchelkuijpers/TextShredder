#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filemanager.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->serverTab, SIGNAL(serverStarted()), this, SLOT(serverDidStart()));
	ui->main_tab_widget->setCurrentWidget(ui->serverTab);
	connect(ui->clientTab, SIGNAL(connectedToHost(int)), this, SLOT(clientConnected(int)));
	connect(ui->clientEditingTab, SIGNAL(clientDisconnected()), this, SLOT(clientDisconnected()));
	connect(FileManager::Instance(), SIGNAL(fileStarted(SyncableFile *)), this, SLOT(fileStarted(SyncableFile *)));

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::serverDidStart()
{
	qDebug("MainWindow::serverDidStart()");
	ui->main_tab_widget->setCurrentWidget(ui->clientEditingTab);
	ui->main_tab_widget->setTabEnabled(0, false);
	ui->main_tab_widget->setTabEnabled(1, false);
	ui->main_tab_widget->setTabEnabled(2, true);
}

void MainWindow::clientDisconnected()
{
	qDebug("MainWindow::clientDisconnected()");
	ui->main_tab_widget->setCurrentWidget(ui->clientTab);
	ui->main_tab_widget->setTabEnabled(0, true);
	ui->main_tab_widget->setTabEnabled(1, true);
	ui->main_tab_widget->setTabEnabled(2, false);
}

void MainWindow::clientConnected(int socketDescriptor)
{
	qDebug("MainWindow::clientConnected()");
	ui->main_tab_widget->setCurrentWidget(ui->clientEditingTab);
	ui->main_tab_widget->setTabEnabled(0, false);
	ui->main_tab_widget->setTabEnabled(1, false);
	ui->main_tab_widget->setTabEnabled(2, true);
	ui->clientEditingTab->startWithSocketDescriptor(socketDescriptor);
}

void MainWindow::fileStarted(SyncableFile * file)
{
	ui->clientEditingTab->startEditingWithFile(file);
}
