#include "clienteditingwindow.h"
#include "ui_clienteditingwindow.h"
#include <QHostAddress>

#define CURSORUPDATESIZE 3

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
	updateCursorPosition();
	qDebug("ClientEditingWindow::updateTextFieldToWorkingCopyContent()");

	disconnect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
	ui->textEdit->setPlainText(*(syncFile->getWorkingCopy()->getContent()));
	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));

	getContentDiffSize();
	updateTextCursor();
	ui->textEdit->setTextCursor(cursor);
	qDebug() << "cursor pos after update: " << cursor.position();
}


void ClientEditingWindow::updateTextCursor()
{
	for( int i=0; i <= diffSize; i++){
		if(beforeCursorText == ui->textEdit->toPlainText().mid(cursorPosition -CURSORUPDATESIZE -i, CURSORUPDATESIZE) ||
		   afterCursorText == ui->textEdit->toPlainText().mid(cursorPosition -i ,CURSORUPDATESIZE)){
			cursor.setPosition(cursorPosition -i, QTextCursor::MoveAnchor);
			break;
		}else if(afterCursorText == ui->textEdit->toPlainText().mid(cursorPosition + i ,CURSORUPDATESIZE) ||
				 beforeCursorText == ui->textEdit->toPlainText().mid(cursorPosition -CURSORUPDATESIZE + i ,CURSORUPDATESIZE)){
			cursor.setPosition(cursorPosition +i, QTextCursor::MoveAnchor);
			break;
		}else{
			cursor.setPosition(cursorPosition, QTextCursor::MoveAnchor);
		}
	}
}

void ClientEditingWindow::getContentDiffSize()
{
	if(ui->textEdit->toPlainText().size() > oldEditWindowSize){
		diffSize = ui->textEdit->toPlainText().size() - oldEditWindowSize;
	}else{
		diffSize = oldEditWindowSize - ui->textEdit->toPlainText().size();
	}

}

void ClientEditingWindow::updateCursorPosition()
{
	cursor = ui->textEdit->textCursor();
	oldEditWindowSize = ui->textEdit->toPlainText().size();

	cursorPosition = cursor.position();
	qDebug() << "cursor pos before update: " << cursorPosition;

	beforeCursorText = ui->textEdit->toPlainText().mid(cursorPosition -CURSORUPDATESIZE, CURSORUPDATESIZE);
	afterCursorText = ui->textEdit->toPlainText().mid(cursorPosition, CURSORUPDATESIZE);
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
