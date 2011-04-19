#include "servertabwindow.h"
#include "ui_servertabwindow.h"
ServerTabWindow::ServerTabWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerTabWindow)
{
    ui->setupUi(this);
}

ServerTabWindow::~ServerTabWindow()
{
    delete ui;
}

void ServerTabWindow::on_startButton_clicked()
{
    int portNumber = ui->portSpinBox->text().toInt();
    if(!server.listen(QHostAddress::Any, portNumber)) {
        qDebug("Could not start the server");
    }
    ui->stopButton->setEnabled(1);
    ui->startButton->setEnabled(0);

	ServerTabWindow::readInputFile();
}

void ServerTabWindow::readInputFile() {

	QFile file(openedFilePath);
	QString fileContent;

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}
		fileContent = file.readAll();
		ui->logBrowser->append(fileContent);

		ServerTabWindow::sendFileContentToClient(fileContent);
}

void ServerTabWindow::sendFileContentToClient(QString fileContent) {

}

void ServerTabWindow::on_stopButton_clicked()
{
    server.close();
    ui->stopButton->setEnabled(0);
    ui->startButton->setEnabled(1);
}

void ServerTabWindow::on_fileSelectButton_clicked()
{
	QFileDialog Qfd;

	openedFilePath = Qfd.getOpenFileName(this, tr("TextShredder File Selector"), QDir::currentPath(), QString("*.txt"));

	QString fileName = openedFilePath.mid(openedFilePath.lastIndexOf("/")+1,openedFilePath.length());

	ui->fileName->setText(fileName);
}
