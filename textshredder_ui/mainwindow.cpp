#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setFixedSize(this->width(),this->height());
	ui->serverIpInput->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_isServerInput_clicked()
{
	if ( ui->isServerInput->isChecked() ) {
		ui->titleLabel1->setText("Start a");
		ui->serverIpInput->setEnabled(false);

		ui->serverIpInput->setText("");
		ui->serverIpInput->setPlaceholderText("Not needed, you are the server.");
		ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/server.svg"));
	} else {
		ui->titleLabel1->setText("Connect to a");
		ui->serverIpInput->setEnabled(true);
		ui->serverIpInput->setText("");
		ui->serverIpInput->setPlaceholderText("Example: 133.214.233.143");
		ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/userfolder.svg"));
		ui->serverIpInput->setFocus();
	}
}
