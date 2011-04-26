#include "clienteditingwindow.h"
#include "ui_clienteditingwindow.h"
#include <QHostAddress>

ClientEditingWindow::ClientEditingWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ClientEditingWindow)
{
    ui->setupUi(this);

	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

ClientEditingWindow::~ClientEditingWindow()
{
    delete ui;
}

void ClientEditingWindow::textChanged(int position, int charsRemoved, int charsAdded )
{
	if(syncFile == NULL)
		return;

	syncFile->getWorkingCopy()->lock();
	QString *workingCopyContent = syncFile->getWorkingCopy()->getContent();
	QString insertString = ui->textEdit->toPlainText().mid(position, charsAdded );
	workingCopyContent->replace(position, charsRemoved, insertString);
	syncFile->getWorkingCopy()->unlock();

	qDebug("\n");
	qDebug() << *(syncFile->getWorkingCopy()->getContent());
}

void ClientEditingWindow::on_disconnectButton_clicked()
{
	clientDisconnected();
}

void ClientEditingWindow::startWithSocketDescriptor(int socketDescriptor)
{
	qDebug("ClientEditingWindow::startWithSocketDescriptor()");
	ui->textEdit->setEnabled(false);
	SyncThread * thread = new SyncThread(this, socketDescriptor, *(new WorkingCopy(this)),
										 false);
	connect(thread, SIGNAL(downloadFinished()), this, SLOT(enableEditing()));
	thread->start();
}

void ClientEditingWindow::enableEditing()
{
	qDebug("ClientEditingWindow::enableEditing()");
	ui->textEdit->setEnabled(true);
	qDebug() << syncFile->getWorkingCopy()->getContent();
	this->updateTextFieldToWorkingCopyContent();
}

void ClientEditingWindow::on_testButton_clicked()
{
	socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1", 1027);
	int socketDescriptor = socket->socketDescriptor();

	SyncThread * thread = new SyncThread(this, socketDescriptor, *(new WorkingCopy(this)),
										 false);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(downloadFinished()), this, SLOT(updateWorkingCopy()));

	//addItemToClientListView();

	thread->start();

}

void ClientEditingWindow::updateWorkingCopy()
{
	qDebug("ClientEditingWindow::updateWorkingCopy()");
	this->updateTextFieldToWorkingCopyContent();
}

void ClientEditingWindow::updateTextFieldToWorkingCopyContent()
{
	qDebug("ClientEditingWindow::updateTextFieldToWorkingCopyContent()");
	disconnect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
	ui->textEdit->setPlainText(*(syncFile->getWorkingCopy()->getContent()));

	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

void ClientEditingWindow::addItemToClientListView(QString ip)
{
	qDebug() << ip;
	ui->clientList->addItem(ip);
}



void ClientEditingWindow::startEditingWithFile(SyncableFile * file)
{
	syncFile = file;
	updateTextFieldToWorkingCopyContent();
	connect(file, SIGNAL(availableClientsChanged()), this, SLOT(updateConnectedClientsTable()));
	qDebug("Got here");
}

void ClientEditingWindow::updateConnectedClientsTable()
{
	QStringList list(syncFile->getAvailableClients());
	ui->clientList->addItems(list);
}

