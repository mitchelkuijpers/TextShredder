#include "servercontrolview.h"
#include "ui_servercontrolview.h"

#include "filemanager.h"

ServerControlView::ServerControlView(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::ServerControlView)
{
	ui->setupUi(this);
	server = new Server(this);
}

ServerControlView::~ServerControlView()
{
    delete ui;
}

void ServerControlView::on_startButton_clicked()
{
	connect(server, SIGNAL(newConnection()),
			this, SLOT(addNewConnectionToLog()));
    int portNumber = ui->portSpinBox->text().toInt();
	if(!server->listen(QHostAddress::Any, portNumber)) {
        qDebug("Could not start the server");
	}

	ui->logBrowser->append("Server started. Ready to accept clients.");

    ui->stopButton->setEnabled(1);
    ui->startButton->setEnabled(0);

	FileManager::Instance()->addFileWithPath(openedFilePath);
	serverStarted();
}


void ServerControlView::on_stopButton_clicked()
{
	server->close();
    ui->stopButton->setEnabled(0);
    ui->startButton->setEnabled(1);
}

void ServerControlView::on_fileSelectButton_clicked()
{
	QFileDialog Qfd;
	openedFilePath = Qfd.getOpenFileName(this, tr("TextShredder File Selector"), QDir::currentPath(), QString("*.txt"));

	QString fileName = openedFilePath.mid(openedFilePath.lastIndexOf("/")+1,openedFilePath.length());
	ui->fileName->setText(fileName);

	if ( !openedFilePath.isEmpty() ) {
		ui->startButton->setEnabled(true);
	} else {
		ui->startButton->setEnabled(false);
		ui->fileName->setText("No File Selected");
	}
}

void ServerControlView::addNewConnectionToLog()
{
	ui->logBrowser->append("New client, connection opened.");
}
