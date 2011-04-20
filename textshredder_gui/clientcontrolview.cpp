#include "clientcontrolview.h"
#include "ui_clientcontrolview.h"

ClientControlView::ClientControlView(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::ClientControlView)
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
	connectedToHost(socketDescriptor);
}
