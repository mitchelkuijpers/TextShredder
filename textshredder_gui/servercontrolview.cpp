#include "servercontrolview.h"
#include "ui_servercontrolview.h"

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
	if(!server->listenWithFile(QHostAddress::Any, portNumber, &fileContent)) {
        qDebug("Could not start the server");
	}

	workingCopy = new WorkingCopy(this);
	QString fileContentString = QString(fileContent);
	workingCopy->setContent(fileContentString);
	qDebug("Z");
	qDebug() << fileContentString;
	qDebug("Y");

	ui->logBrowser->append("Server started. Ready to accept clients.");

    ui->stopButton->setEnabled(1);
    ui->startButton->setEnabled(0);

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

	readSelectedFile();
}

void ServerControlView::readSelectedFile()
{
	QFile file(openedFilePath);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		ui->logBrowser->append("No file selected, try again.");
		ui->startButton->setEnabled(0);
		return;
	}

	fileContent = file.readAll();
	ui->logBrowser->append("File selected. Ready to start server.");
	ui->startButton->setEnabled(1);
}

void ServerControlView::addNewConnectionToLog()
{
	ui->logBrowser->append("New client, connection opened.");
}

WorkingCopy * ServerControlView::getWorkingCopy()
{
	return workingCopy;
}
