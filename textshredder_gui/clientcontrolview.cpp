#include "clientcontrolview.h"
#include "ui_clientcontrolview.h"
#include "filemanager.h"
#include "syncablefile.h"

ClientControlView::ClientControlView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ClientControlView),  connection(NULL)
{
    ui->setupUi(this);
}

ClientControlView::~ClientControlView()
{
    delete ui;
}


void ClientControlView::on_connectButton_clicked()
{
	QString portText(ui->portSpinner->text());
	QString hostname(ui->serverAdressLineEdit->text());
	int port = portText.toInt();
	QTcpSocket socket(this);
	socket.connectToHost(hostname, port);
	int socketDescriptor = socket.socketDescriptor();
	if (connection != NULL)
		delete connection;
	connection = new TextShredderConnection(this, socketDescriptor);

	FileManager::Instance()->addSyncFile(new SyncableFile(this));
}
