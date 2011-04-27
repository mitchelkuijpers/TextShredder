#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filemanager.h"
#include "clienteditingwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->serverTab, SIGNAL(serverStarted()), this, SLOT(serverDidStart()));
	ui->main_tab_widget->setCurrentWidget(ui->serverTab);
	connect(FileManager::Instance(), SIGNAL(fileStarted(SyncableFile *)),
			this, SLOT(fileStarted(SyncableFile *)));
	connect(FileManager::Instance(), SIGNAL(availableFilesChanged()),
			this, SLOT(updateAvailableFiles()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::serverDidStart()
{
}

void MainWindow::editingDisconnected()
{
	qDebug("MainWindow::editingDisconnected()");
	ClientEditingWindow *editingWindow = (ClientEditingWindow *) sender();
	int tabIndex = ui->main_tab_widget->indexOf (editingWindow);
	ui->main_tab_widget->removeTab (tabIndex);
	delete editingWindow;

	ui->main_tab_widget->setCurrentWidget(ui->serverTab);
}

void MainWindow::fileStarted(SyncableFile * file)
{
	ClientEditingWindow *editingWindow = new ClientEditingWindow(this);
	connect(editingWindow, SIGNAL(clientDisconnected()), this, SLOT(editingDisconnected()));
	ui->main_tab_widget->addTab (editingWindow, file->getFileAlias());
	editingWindow->startEditingWithFile (file);
	ui->main_tab_widget->setCurrentWidget (editingWindow);
}

void MainWindow::updateAvailableFiles()
{
	while (ui->availableFilesList->count () > 0) {
		ui->availableFilesList->takeItem(0);
	}
	QList<QString> nameList;
	FileManager::Instance ()->fillListWithAllFileNames (nameList);
	ui->availableFilesList->addItems(nameList);
}
