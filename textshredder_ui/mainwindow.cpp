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

	setDefaultFont();

	ui->titleLabelServer->hide();

	performStarupAnimation();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDefaultFont()
{
	QFont defaultFont("Cantarell");
	this->setFont(defaultFont);
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
	ui->titleLabelServer->show();
	ui->titleLabelClient->hide();

	ui->serverIpInput->setEnabled(false);

	ui->serverIpInput->setText("");
	ui->serverIpInput->setPlaceholderText("Not needed, you are the server.");
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/server.svg"));
}

void MainWindow::changeWindowStateToClient()
{
	ui->titleLabelServer->hide();
	ui->titleLabelClient->show();
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

void MainWindow::performStarupAnimation()
{
	animationMoveTo(ui->fadeInLabel, QRect(0, 47, 550, 121),
					QRect(500, 47, 550, 121), 800);

	animationMoveTo(ui->titleLabelClient, QRect(300, 20, 451, 141), QRect(110, 20, 451, 141), 500);
	animationMoveTo(ui->titleLabelServer, QRect(300, 15, 451, 141), QRect(110, 15, 451, 141), 500);
	animationMoveTo(ui->titleLabelHead, QRect(350, 67, 451, 141), QRect(112, 67, 451, 141), 500);
}

void MainWindow::animationMoveTo(QObject * target, QRect startRect, QRect endRect, int animationLength )
{
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	animation->setDuration(animationLength);
	animation->setStartValue(startRect);
	animation->setEndValue(endRect);

	animation->start();
}
