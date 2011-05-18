#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notificationmanager.h"

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include "../textshredder_core/server/server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow), client(NULL)
{
	ConfigurationManager * config = ConfigurationManager::Instance();
	ConfigurationOptions configOptions(this);

	config->load();

    ui->setupUi(this);
	this->setFixedSize(this->width(),this->height());
	ui->serverIpInput->setFocus();

	ui->serverIpInput->setText();
	//setDefaultFont();

	ui->titleLabelServer->hide();

	performTextSlideInAnimation();
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

	performTextSlideInAnimation();
}

void MainWindow::changeWindowStateToServer()
{
	ui->connectButton->setText("Start");
	ui->titleLabelServer->show();
	ui->titleLabelClient->hide();
	ui->serverIpInput->setEnabled(false);
	ui->serverIpInput->setText("");
	ui->serverIpInput->setPlaceholderText("Not needed, you are the server.");
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/server.svg"));
}

void MainWindow::changeWindowStateToClient()
{
	ui->connectButton->setText("Connect");
	ui->titleLabelServer->hide();
	ui->titleLabelClient->show();
	ui->serverIpInput->setEnabled(true);
	ui->serverIpInput->setText("");
	ui->serverIpInput->setPlaceholderText("Example: 133.214.233.143");
	ui->serverIpInput->setText("127.0.0.1");
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/userfolder.svg"));
	ui->serverIpInput->setFocus();
}

void MainWindow::on_cancelButton_clicked()
{
	//Create options
	QList<NotificationOption> options;
	NotificationOption option3(this ,"No");
	NotificationOption option4(this ,"Yes");
	options.append(option3);
	options.append(option4);

	//Create notification
	Notification notification(this, "Are you sure you want to quit TextShredder?", 2, options);
	NotificationManager::Instance()->createNotificationDialog(notification);
}

void MainWindow::functionToExecute()
{
	qDebug("You clicked on a dialog button!");
}

void MainWindow::performTextSlideInAnimation()
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

void MainWindow::on_connectButton_clicked()
{
	if (ui->isServerInput->isChecked()) {
		Server *serv = Server::Instance();
		quint16 port = ui->serverPortInput->value();
		serv->listen(QHostAddress::Any, port);
		this->hide();
		editorView.show();
		editorView.setToServerMode();
	} else {
		if (client == NULL) {
			client = new Client(this);
			connect(client, SIGNAL(clientConnected()), this, SLOT(clientDidConnect()));
		}
		QHostAddress address(ui->serverIpInput->text());

		quint16 port = ui->serverPortInput->value();

		client->connectToServer(address, port);
		editorView.setToClientMode();
		qDebug("TODO: start cool-animation, en aftrekken op de meisjes wc wouter");
	}
	if(ui->rememberSettingsInput->isChecked()) {
		saveSettings();
	}
}

void MainWindow::saveSettings()
{
	ConfigurationManager * config = ConfigurationManager::Instance();
	ConfigurationOptions configOptions(this);
	TextShredderConnection connectionInfo(this);
	configOptions.setIp(ui->serverIpInput->text());

	if(ui->isServerInput->isChecked()) {
		configOptions.setIp(connectionInfo.getPeerAdress());
	}
	configOptions.setServerPort((quint16) ui->serverPortInput->value());

	config->setConfigurationOptions(configOptions);

	config->save();
}

void MainWindow::clientDidConnect() {
	qDebug("TODO: end started-cool-animation, en aftrekken op de meisjes wc wouter");
	this->hide();
	editorView.show();
}
