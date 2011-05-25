#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../textshredder_core/libraries/notification/notificationmanager.h"
#include "../textshredder_core/libraries/configuration/configurationmanager.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QHostAddress>
#include <QNetworkInterface>

#include "../textshredder_core/server/server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ConfigurationManager::Instance()->load();
	ConfigurationOptions configOptions = ConfigurationManager::Instance()->getConfigurationOptions();
    ui->setupUi(this);

	this->setFixedSize(this->width(),this->height());

	ui->serverIpInput->setFocus();
	ui->aliasInput->setText(configOptions.getLastUsedAlias());
	ui->aliasInput->setFocus();

	ui->serverIpInput->addItem(configOptions.getLastKnownIp());
	int i;
	for(i = 0; i < configOptions.getKnownHostsList().count(); i++){
		if(configOptions.getKnownHostsList().at(i) != configOptions.getLastKnownIp()) {
			ui->serverIpInput->addItem(configOptions.getKnownHostsList().at(i));
		}
	}
	//setDefaultFont();
	if(configOptions.getServerPort() != 0) {
		ui->serverPortInput->setValue(configOptions.getServerPort());
	}
	ui->connectingLoader->hide();
	ui->titleLabelServer->hide();

	performTextSlideInAnimation();

	QRegExp re( "[0-9a-zA-Z]*" );
	QRegExpValidator *validator = new QRegExpValidator(re, ui->aliasInput);
	ui->aliasInput->setValidator(validator);
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

	performTextSlideInAnimation();
}

void MainWindow::changeWindowStateToServer()
{
	ui->connectButton->setText("Start");
	ui->titleLabelServer->show();
	ui->titleLabelClient->hide();
	ui->serverIpInput->setEnabled(false);
	ui->serverIpInput->setEditText("Your IP: " + QString(QNetworkInterface::allAddresses().at(4).toString()));
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/server.svg"));
}

void MainWindow::changeWindowStateToClient()
{
	ui->connectButton->setText("Connect");
	ui->titleLabelServer->hide();
	ui->titleLabelClient->show();
	ui->serverIpInput->setEnabled(true);
	ui->serverIpInput->setEditText("127.0.0.1");
	ui->avatarLabel->setPixmap(QPixmap(":/ui/main/images/userfolder.svg"));
	ui->aliasInput->setFocus();
}

void MainWindow::on_cancelButton_clicked()
{
	Notification notification(this, "You have clicked the cancel button!\nNothing happens.", 4);
	NotificationManager::Instance()->createNotificationDialog(notification);
}

void MainWindow::functionToExecute()
{
	//Test function for notificationmanager
	//Has to be executed when this function is assigned to a button (onclick)
	qDebug("You clicked on a dialog button!");
}

void MainWindow::performTextSlideInAnimation()
{
	animationMoveTo(ui->titleLabelClient, QRect(350, 0, 451, 141), QRect(100, 0, 451, 141), 500);
	animationMoveTo(ui->titleLabelServer, QRect(350, 0, 451, 141), QRect(100, 0, 451, 141), 500);
	animationMoveTo(ui->titleLabelHead, QRect(400, 45, 451, 141), QRect(100, 45, 451, 141), 500);
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

bool MainWindow::validateAliasInput()
{
	if (ui->aliasInput->text().length() == 0) {
		return false;
	}
	return true;
}

void MainWindow::on_connectButton_clicked()
{
	if (!validateAliasInput()) {
		qDebug() << "TODO: MainWindow::on_connectButton_clicked" << "Show info balloon or notification or even disable the connect if nothing is filled into the alias field";
		return;
	}
	ui->connectButton->setEnabled(false);
	FileManager::Instance()->setServerSide(ui->isServerInput->isChecked());

	if (ui->isServerInput->isChecked()) {
		Server *serv = Server::Instance();
		serv->setServerAlias(ui->aliasInput->text());
		quint16 port = ui->serverPortInput->value();
		serv->listen(QHostAddress::Any, port);
		this->hide();
		editorView.show();
		editorView.setToServerMode();
	} else {
		QSharedPointer<Client> client = Client::Instance();
		client.data()->setAlias(ui->aliasInput->text());
		connect(client.data(), SIGNAL(clientConnected()), this, SLOT(clientDidConnect()));
		connect(client.data(), SIGNAL(clientConnectionError(QAbstractSocket::SocketError)),
				this, SLOT(clientHadError(QAbstractSocket::SocketError)));
		QHostAddress address(ui->serverIpInput->currentText());

		quint16 port = ui->serverPortInput->value();

		client.data()->connectToServer(address, port);
		editorView.setToClientMode();

		ui->connectingLoader->show();

	}
	if(ui->rememberSettingsInput->isChecked()) {
		saveSettings();
	}
}

void MainWindow::saveSettings()
{
	ConfigurationManager::Instance()->load();
	ConfigurationOptions configOptions = ConfigurationManager::Instance()->getConfigurationOptions();
	configOptions.setServerPort((quint16) ui->serverPortInput->value());

	if(ui->aliasInput->text().length() > 0) {
		QString cleanedAlias = ui->aliasInput->text().remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\]\\\\]")));
		configOptions.setLastUsedAlias(cleanedAlias);
	}
	else {
		Notification notification(this, "The specified alias can only contain alphanumeric characters and must be longer then 1 character!", 2, true);
		NotificationManager::Instance()->createNotificationDialog(notification);
		ui->aliasInput->setFocus();
		ui->connectButton->setEnabled(true);
		ui->connectingLoader->hide();
	}
	if(ui->serverIpInput->isEnabled()) {
		configOptions.addHostToKnownHostsList(ui->serverIpInput->currentText());
		configOptions.setLastKnownIp(ui->serverIpInput->currentText());
	}

	ConfigurationManager::Instance()->setConfigurationOptions(configOptions);
	ConfigurationManager::Instance()->save();
}

void MainWindow::clientDidConnect() {
	this->hide();
	editorView.show();
}

void MainWindow::clientHadError(QAbstractSocket::SocketError error)
{
	displayErrorNotification(error);
	ui->connectButton->setEnabled(true);
	ui->connectingLoader->hide();
}

void MainWindow::displayErrorNotification(QAbstractSocket::SocketError error)
{
	Notification notification(this, "", 2, true);

	switch( error ) {
		case 0:
				notification.setMessage("The connection was refused by the peer (or timed out).");
				break;
		case 1:
				notification.setMessage("The remote host closed the connection.\nNote that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.");
				break;
		case 2:
				notification.setMessage("The host address was not found.");
				break;
		case 3:
				notification.setMessage("The socket operation failed because the application lacked the required privileges.");
				break;
		case 4:
				notification.setMessage("The local system ran out of resources (e.g., too many sockets).");
				break;
		case 5:
				notification.setMessage("The socket operation timed out.");
				break;
		case 6:
				notification.setMessage("The datagram was larger than the operating system's limit\n(which can be as low as 8192 bytes).");
				break;
		case 7:
				notification.setMessage("An error occurred with the network\n(e.g., the network cable was accidentally plugged out).");
				break;
		case 8:
				notification.setMessage("The address specified to QUdpSocket::bind()\nis already in use and was set to be exclusive.");
				break;
		case 9:
				notification.setMessage("The address specified to QUdpSocket::bind()\ndoes not belong to the host.");
				break;
		case 10:
				notification.setMessage("The requested socket operation is not supported\nby the local operating system (e.g., lack of IPv6 support).");
				break;
		case 11:
				notification.setMessage("Used by QAbstractSocketEngine only, The last operation\nattempted has not finished yet (still in progress in the background).");
				break;
		case 12:
				notification.setMessage("The socket is using a proxy, and the proxy requires authentication.");
				break;
		case 13:
				notification.setMessage("The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)");
				break;
		case 14:
				notification.setMessage("Could not contact the proxy server because the connection to that server was denied");
				break;
		case 15:
				notification.setMessage("The connection to the proxy server was closed\nunexpectedly (before the connection to the final peer was established)");
				break;
		case 16:
				notification.setMessage("The connection to the proxy server timed out\nor the proxy server stopped responding in the authentication phase.");
				break;
		case 17:
				notification.setMessage("The proxy address set with setProxy() (or the application proxy) was not found.");
				break;
		case 18:
				notification.setMessage("The connection negotiation with the proxy server,\nbecause the response from the proxy server could not be understood.");
				break;
		case -1:
				notification.setMessage("An unidentified error occurred.");
				break;
	}

	NotificationManager::Instance()->createNotificationDialog(notification);
}
