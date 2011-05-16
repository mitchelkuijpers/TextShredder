#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notification.h"
#include "notificationoption.h"
#include "notificationmanager.h"
#include <QTcpSocket>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
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
	performStarupAnimation();
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
	performStarupAnimation();
}

void MainWindow::on_cancelButton_clicked()
{
	//Create options
	QList<NotificationOption> options;
	NotificationOption option3(NULL ,"Cancel");
	NotificationOption option4(NULL ,"Continue");
	options.append(option3);
	options.append(option4);

	//Create notification
	Notification notification(NULL, "This is a succes message.", 0, options);
	NotificationManager::Instance()->createNotificationDialog(notification);

	performStarupAnimation();
}

void MainWindow::performStarupAnimation()
{
	animationMoveTo(ui->titleLabelClient, QRect(300, 20, 451, 141), QRect(110, 20, 451, 141), 500);
	animationMoveTo(ui->titleLabelServer, QRect(300, 15, 451, 141), QRect(110, 15, 451, 141), 500);
	animationMoveTo(ui->titleLabelHead, QRect(350, 67, 451, 141), QRect(112, 67, 451, 141), 500);
}

void MainWindow::animationMoveTo(QWidget * target, QRect startRect, QRect endRect, int animationLength )
{
	QPropertyAnimation *animation = new QPropertyAnimation(target, "geometry");
	animation->setDuration(animationLength);
	animation->setStartValue(startRect);
	animation->setEndValue(endRect);
	animation->setEasingCurve(QEasingCurve::OutBack);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}
