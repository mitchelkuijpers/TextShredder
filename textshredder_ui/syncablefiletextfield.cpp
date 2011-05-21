#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"
#include <QFileDialog>

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField),
	beforeRemovedEditsEditSize(0)
{
    ui->setupUi(this);

	WorkingCopy * workingCopy = file.data()->getWorkingCopy().data();
	connect(workingCopy, SIGNAL(workingCopyChanged()), this, SLOT(workingCopyChanged()));
	ui->textEditorField->setText(QString(*(workingCopy->getContent())));
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

	if(!Patches.isEmpty()){
		qDebug() << Patches.first().toString();
		if((Patches.first().diffs.at(0).operation == 0 ||
		   Patches.first().diffs.at(0).operation == 1) ){
			if(position == 0){
				beforeRemovedEditsEditSize = charsAdded - charsRemoved;
			}else{
				beforeRemovedEditsEditSize = 0;
			}
		}else if((Patches.first().diffs.at(1).operation == 0 ||
				 Patches.first().diffs.at(1).operation == 1)){
			if(position < (Patches.first().start1 + Patches.first().diffs.at(0).text.size())){
				beforeRemovedEditsEditSize = charsAdded - charsRemoved;
			}else{
				beforeRemovedEditsEditSize =0;
			}
		}else{
			beforeRemovedEditsEditSize = 0;
		}
	}

	qDebug() << "deleteTimer";
	//deleteTimer->stop();
	qDebug() << "deleteTimer done";
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
	QString temp = ui->textEditorField->toPlainText();
	Patches = syncFile->getWorkingCopy()->getPatchesToConvertString(temp);
	qDebug() << "Patches: " << Patches.first().toString();
	ui->textEditorField->setPlainText(*(syncFile->getWorkingCopy()->getContent()));

	EditDeleteColor();
	highlighter->setPatches(Patches);
	highlighter->rehighlight();
	highlighter->clearPatches();

	connect(timer, SIGNAL(timeout()), this, SLOT(clearHighlights()));
	timer->start(2000);




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
	if(Patches.first().diffs.count() >= 2){
		if(Patches.first().diffs.at(0).operation == 1){
			deletedEdit = Patches.first().diffs.first().text;
			deletedEdit.append(ui->textEditorField->toPlainText());

			startDeleteColorTimer();
		}else if(Patches.first().diffs.at(1).operation == 1){
			deletedEdit = ui->textEditorField->toPlainText();
			deletedEdit.insert(Patches.first().start1 +
									Patches.first().diffs.first().text.size(),
									Patches.first().diffs.at(1).text);
			startDeleteColorTimer();
		}
	}
}

void SyncableFileTextField::startDeleteColorTimer()
{
	ui->textEditorField->setPlainText(deletedEdit);
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

	removeDeletes();

	deleteTimer->blockSignals(true);
	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

void SyncableFileTextField::removeDeletes()
{
	QString temp;

	if(Patches.first().diffs.at(0).operation == 1){
		if(ui->textEditorField->toPlainText().mid(0, Patches.first().diffs.at(0).text.size()) ==
		   Patches.first().diffs.at(0).text){
			temp = ui->textEditorField->toPlainText().remove(Patches.first().start1, Patches.first().diffs.at(0).text.size());
			ui->textEditorField->setPlainText(temp);
		}
	}else if(Patches.first().diffs.at(1).operation == 1){
		if(ui->textEditorField->toPlainText().mid(Patches.first().start1 + Patches.first().diffs.at(0).text.size(),
												  Patches.first().diffs.at(1).text.size()) == Patches.first().diffs.at(1).text){
			temp = ui->textEditorField->toPlainText().remove(Patches.first().start1 + Patches.first().diffs.at(0).text.size() +
															 beforeRemovedEditsEditSize, Patches.first().diffs.at(1).text.size());
			ui->textEditorField->setPlainText(temp);
		}
	}

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

void SyncableFileTextField::on_saveFileButton_clicked()
{
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"),
							   QDir::currentPath(),
							   tr("Text File (*.txt);;TextShredder Document (*.tsd);;HTML File (*.html)"));

	if ( !filePath.isEmpty() ) {
		QFile file(filePath);

		QFileInfo info(filePath);
		QString fileExtension(info.suffix());
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&file);

		if ( fileExtension.compare("html") == 0 ) {
			out << ui->textEditorField->toHtml();
		} else {
			out << ui->textEditorField->toPlainText();
		}

	}
}
