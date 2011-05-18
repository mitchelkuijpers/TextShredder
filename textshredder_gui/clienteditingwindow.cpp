#include "clienteditingwindow.h"
#include "ui_clienteditingwindow.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include <QHostAddress>
#include <QSyntaxHighlighter>

#define CURSORUPDATESIZE 3

ClientEditingWindow::ClientEditingWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ClientEditingWindow)
{
    ui->setupUi(this);
	timer = new QTimer(this);
	deleteTimer = new QTimer(this);
	highlighter = new ClientHighlighting(ui->textEdit->document());
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



	qDebug() << "doc:" << ui->textEdit->document()->toPlainText();
	if(!syncFile->getWorkingCopy()->getContent()->isNull()){
		QString temp = ui->textEdit->document()->toPlainText();

		if(syncFile->getWorkingCopy()->getContent() != temp){
			Patches = syncFile->getWorkingCopy()->getPatchesToConvertString(temp);

			ui->textEdit->setPlainText(*(syncFile->getWorkingCopy()->getContent()));


			EditDeleteColor();

			highlighter->setPatches(Patches);
			highlighter->rehighlight();
			highlighter->clearPatches();
			connect(timer, SIGNAL(timeout()), this, SLOT(clearHighlights()));

			timer->start(2000);
		}

	}

	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));


	updateTextCursor();
	ui->textEdit->setTextCursor(cursor);
}


void ClientEditingWindow::EditDeleteColor()
{
	QString deletedEditSecond;
	if(Patches.first().diffs.count() >= 2){
		if(Patches.first().diffs.at(0).operation == 1){
			deletedEditFirst = Patches.first().diffs.first().text;
			deletedEditFirst.append(ui->textEdit->toPlainText());

			startDeleteColorTimer();

		}else if(Patches.first().diffs.at(1).operation == 1){
			deletedEditFirst = ui->textEdit->toPlainText().mid(0,Patches.first().start1 + Patches.first().diffs.first().text.size());
			deletedEditSecond = ui->textEdit->toPlainText().mid(Patches.first().start1+ Patches.first().diffs.first().text.size(),
																ui->textEdit->toPlainText().size());
			deletedEditFirst.append(Patches.first().diffs.at(1).text);
			deletedEditFirst.append(deletedEditSecond);

			startDeleteColorTimer();

		}

	}
}

void ClientEditingWindow::startDeleteColorTimer()
{
	ui->textEdit->setPlainText(deletedEditFirst);
	connect(deleteTimer, SIGNAL(timeout()), this, SLOT(deleteEdits()));
	deleteTimer->start(1000);
	deleteTimer->blockSignals(false);
}

void ClientEditingWindow::clearHighlights()
{
	highlighter->rehighlight();

}

void ClientEditingWindow::deleteEdits()
{
	disconnect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
	qDebug() << "Workingcopy before delete:" << *(syncFile->getWorkingCopy()->getContent());

	if(!(syncFile->getWorkingCopy()->getContent())->isEmpty()){
		ui->textEdit->setPlainText(*(syncFile->getWorkingCopy()->getContent()));
	}
	deleteTimer->blockSignals(true);
	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}


void ClientEditingWindow::updateTextCursor()
{
	getContentDiffSize();
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
