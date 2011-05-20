#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField)
{
    ui->setupUi(this);

	WorkingCopy * fileContents = file.data()->getWorkingCopy();
	connect(file->getWorkingCopy (), SIGNAL(workingCopyChanged()), this, SLOT(workingCopyChanged()));
	ui->textEditorField->setText(QString(*fileContents->getContent()));
	timer = new QTimer(this);
	deleteTimer = new QTimer(this);
	highlighter = new EditorHighLighting(ui->textEditorField->document());

	syncFile = file.data();

	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

SyncableFileTextField::~SyncableFileTextField()
{
    delete ui;
}

void SyncableFileTextField::textChanged(int position, int charsRemoved, int charsAdded )
{
	if(syncFile == NULL)
		return;

	syncFile->getWorkingCopy()->lock();
	QString *workingCopyContent = syncFile->getWorkingCopy()->getContent();
	QString insertString = ui->textEditorField->toPlainText().mid(position, charsAdded );
	workingCopyContent->replace(position, charsRemoved, insertString);
	syncFile->getWorkingCopy()->unlock();
}

void SyncableFileTextField::updateTextFieldToWorkingCopyContent()
{
	updateCursorPosition();
	qDebug("ClientEditingWindow::updateTextFieldToWorkingCopyContent()");

	disconnect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));


	//still needs some clean up
	if(*syncFile->getWorkingCopy()->getContent() != ""){
		QString temp = ui->textEditorField->toPlainText();
		if(*syncFile->getWorkingCopy()->getContent() != temp){
			Patches = syncFile->getWorkingCopy()->getPatchesToConvertString(temp);
			qDebug() << "Patches: " << Patches.first().toString();
			ui->textEditorField->setPlainText(*(syncFile->getWorkingCopy()->getContent()));

			EditDeleteColor();
			highlighter->setPatches(Patches);
			highlighter->rehighlight();
			highlighter->clearPatches();

			connect(timer, SIGNAL(timeout()), this, SLOT(clearHighlights()));
			timer->start(2000);
		}
	}


	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));

	getContentDiffSize();
	updateTextCursor();
	ui->textEditorField->setTextCursor(cursor);
	qDebug() << "cursor pos after update: " << cursor.position();
}

void SyncableFileTextField::EditDeleteColor()
{
	//also needs some clean up
	QString deletedEditSecond;
	if(Patches.first().diffs.count() >= 2){
		if(Patches.first().diffs.at(0).operation == 1){
			deletedEditFirst = Patches.first().diffs.first().text;
			deletedEditFirst.append(ui->textEditorField->toPlainText());

			startDeleteColorTimer();
		}else if(Patches.first().diffs.at(1).operation == 1){
			deletedEditFirst = ui->textEditorField->toPlainText().mid(0,Patches.first().start1 + Patches.first().diffs.first().text.size());
			deletedEditSecond = ui->textEditorField->toPlainText().mid(Patches.first().start1+ Patches.first().diffs.first().text.size(),
																ui->textEditorField->toPlainText().size());
			deletedEditFirst.append(Patches.first().diffs.at(1).text);
			deletedEditFirst.append(deletedEditSecond);

			startDeleteColorTimer();

		}

	}
}

void SyncableFileTextField::startDeleteColorTimer()
{
	ui->textEditorField->setPlainText(deletedEditFirst);
	connect(deleteTimer, SIGNAL(timeout()), this, SLOT(deleteEdits()));
	deleteTimer->start(1000);
	deleteTimer->blockSignals(false);
}

void SyncableFileTextField::clearHighlights()
{
	highlighter->rehighlight();

}

void SyncableFileTextField::deleteEdits()
{
	disconnect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
	qDebug() << "Workingcopy before delete:" << *(syncFile->getWorkingCopy()->getContent());

	if(!(syncFile->getWorkingCopy()->getContent())->isEmpty()){
		ui->textEditorField->setPlainText(*(syncFile->getWorkingCopy()->getContent()));
	}
	deleteTimer->blockSignals(true);
	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}


void SyncableFileTextField::updateTextCursor()
{
	for( int i=0; i <= diffSize; i++){
		if(beforeCursorText == ui->textEditorField->toPlainText().mid(cursorPosition -CURSORUPDATESIZE -i, CURSORUPDATESIZE) ||
		   afterCursorText == ui->textEditorField->toPlainText().mid(cursorPosition -i ,CURSORUPDATESIZE)){
			cursor.setPosition(cursorPosition -i, QTextCursor::MoveAnchor);
			break;
		}else if(afterCursorText == ui->textEditorField->toPlainText().mid(cursorPosition + i ,CURSORUPDATESIZE) ||
				 beforeCursorText == ui->textEditorField->toPlainText().mid(cursorPosition -CURSORUPDATESIZE + i ,CURSORUPDATESIZE)){
			cursor.setPosition(cursorPosition +i, QTextCursor::MoveAnchor);
			break;
		}else{
			cursor.setPosition(cursorPosition, QTextCursor::MoveAnchor);
		}
	}
}

void SyncableFileTextField::getContentDiffSize()
{
	if(ui->textEditorField->toPlainText().size() > oldEditWindowSize){
		diffSize = ui->textEditorField->toPlainText().size() - oldEditWindowSize;
	}else{
		diffSize = oldEditWindowSize - ui->textEditorField->toPlainText().size();
	}

}

void SyncableFileTextField::updateCursorPosition()
{
	cursor = ui->textEditorField->textCursor();
	oldEditWindowSize = ui->textEditorField->toPlainText().size();

	cursorPosition = cursor.position();

	beforeCursorText = ui->textEditorField->toPlainText().mid(cursorPosition -CURSORUPDATESIZE, CURSORUPDATESIZE);
	afterCursorText = ui->textEditorField->toPlainText().mid(cursorPosition, CURSORUPDATESIZE);
}

void SyncableFileTextField::workingCopyChanged()
{
	this->updateTextFieldToWorkingCopyContent();
}