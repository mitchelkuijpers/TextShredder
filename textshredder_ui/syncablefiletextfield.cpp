#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField)
{
    ui->setupUi(this);

	WorkingCopy * fileContents = file.data()->getWorkingCopy();
	ui->textEditorField->setText(QString(*fileContents->getContent()));

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
	ui->textEditorField->setPlainText(*(syncFile->getWorkingCopy()->getContent()));
	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));

	getContentDiffSize();
	updateTextCursor();
	ui->textEditorField->setTextCursor(cursor);
	qDebug() << "cursor pos after update: " << cursor.position();
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
	qDebug() << "cursor pos before update: " << cursorPosition;

	beforeCursorText = ui->textEditorField->toPlainText().mid(cursorPosition -CURSORUPDATESIZE, CURSORUPDATESIZE);
	afterCursorText = ui->textEditorField->toPlainText().mid(cursorPosition, CURSORUPDATESIZE);
}
