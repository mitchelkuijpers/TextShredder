#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QPropertyAnimation>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setFixedSize(this->width(),this->height());
	ui->serverIpInput->setFocus();

	animationMoveTo(ui->fadeInLabel, QRect(0, 60, 541, 91), QRect(500, 60, 541, 91), 700);
	animationMoveTo(ui->titleLabel1, QRect(350, 69, 211, 31), QRect(100, 69, 211, 31), 600);
	animationMoveTo(ui->titleLabel2, QRect(300, 109, 241, 41), QRect(100, 109, 241, 41), 610);
	animationMoveTo(ui->titleLabel3, QRect(540, 110, 141, 40), QRect(340, 110, 141, 40), 610);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_isServerInput_clicked()
{
	if ( ui->isServerInput->isChecked() ) {
		changeWindowStateToServer();
	} else {
		changeWindowStateToClient();
	}
}

void MainWindow::changeWindowStateToServer()
{
	ui->titleLabel1->setText("Start a");
	ui->serverIpInput->setEnabled(false);

	ui->serverIpInput->setText("");
	ui->serverIpInput->setPlaceholderText("Not needed, you are the server.");
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/server.svg"));
}

void MainWindow::changeWindowStateToClient()
{
	ui->titleLabel1->setText("Connect to a");
	ui->serverIpInput->setEnabled(true);
	ui->serverIpInput->setText("");
	ui->serverIpInput->setPlaceholderText("Example: 133.214.233.143");
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/userfolder.svg"));
	ui->serverIpInput->setFocus();
}

void MainWindow::animationMoveTo(QObject * target, QRect startRect, QRect endRect, int animationLength )
{
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	animation->setDuration(animationLength);
	animation->setStartValue(startRect);
	animation->setEndValue(endRect);

	animation->start();
}
