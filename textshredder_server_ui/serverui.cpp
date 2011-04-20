#include "serverui.h"
#include "ui_serverui.h"

ServerUI::ServerUI(QWidget *parent) :
	QTcpSocket(parent),
    ui(new Ui::ServerUI)
{
	startServerWithDefaultFileContentsAndPort();

    ui->setupUi(this);
}

ServerUI::~ServerUI()
{
    delete ui;
}


void ServerUI::startServerWithDefaultFileContentsAndPort()
{
	fileContent = "This is nice file content!\nHaha";

	server = new Server(this);

	if( !server->listenWithFile( QHostAddress::Any, PORTNUMBER, &fileContent ) ) {
		qDebug("Could not start the server");
	}
}
