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
	//connect(ui->saveButton, SIGNAL(fileSaved()), this, SLOT(saveFileMe()));
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

	qDebug() << *(syncFile->getWorkingCopy()->getContent());
}

void ClientEditingWindow::on_disconnectButton_clicked()
{
	emit clientDisconnected();

	qDebug("Stopped");

}

void ClientEditingWindow::on_saveButton_clicked()
{
	saveFileMe();
	//emit fileSaved();
	qDebug("Saved");
}

void ClientEditingWindow::enableEditing()
{
	this->updateTextFieldToWorkingCopyContent();
}


void ClientEditingWindow::updateWorkingCopy()
{
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

	qDebug("C");
}

void ClientEditingWindow::startEditingWithFile(SyncableFile * file)
{
	syncFile = file;
	updateTextFieldToWorkingCopyContent();
	connect(file, SIGNAL(availableClientsChanged()), this, SLOT(updateConnectedClientsTable()));
	//TODO: make this connect go through the SyncableFile
	connect(file->getWorkingCopy (), SIGNAL(workingCopyChanged()), this, SLOT(workingCopyChanged()));
}

void ClientEditingWindow::updateConnectedClientsTable()
{
	while (ui->clientList->count () > 0) {
		ui->clientList->takeItem(0);
	}
	QStringList list(syncFile->getAvailableClients());
	ui->clientList->addItems(list);
}

void ClientEditingWindow::workingCopyChanged()
{
	this->updateTextFieldToWorkingCopyContent();
}

void ClientEditingWindow::saveFileMe()
{
	saveFileAs();
	/*if(saveFilePath == "untitled.txt"){
		saveFileAs();
	}else{
		saveFile(saveFilePath);
	}*/
}

void ClientEditingWindow::saveFile(const QString &name)
{
	QFile file(name);
	if (file.open(QIODevice::WriteOnly|QIODevice::Text))
	{
		file.write(ui->textEdit->toPlainText().toUtf8());

	}
}

void ClientEditingWindow::saveFileAs()
{
	saveFilePath = QFileDialog::getSaveFileName(this);
	if(saveFilePath == "untitled.txt"){
		return;
	}
	saveFile(saveFilePath);
}
