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

	fadeInWindow();
	QFont defaultFont("Cantarell");

	this->setFont(defaultFont);

	performStarupAnimation();
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

void MainWindow::on_cancelButton_clicked()
{
	performStarupAnimation();
}

void MainWindow::fadeInWindow()
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(500);
	animation->setStartValue(0);
	animation->setEndValue(1);

	animation->start();
}

void MainWindow::performStarupAnimation()
{
	animationMoveTo(ui->fadeInLabel, QRect(0, 20, 541, 121), QRect(500, 20, 541, 121), 800);
	animationMoveTo(ui->titleLabel1, QRect(300, 20, 541, 121), QRect(50, 20, 541, 121), 600);
}

void MainWindow::animationMoveTo(QObject * target, QRect startRect, QRect endRect, int animationLength )
{
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	animation->setDuration(animationLength);
	animation->setStartValue(startRect);
	animation->setEndValue(endRect);

	animation->start();
}
