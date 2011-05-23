#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"
#include <QFileDialog>

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField),
	beforeRemovedEditsEditSize(0)
{
    ui->setupUi(this);

	syncFile = file;
	connect(syncFile.data()->getWorkingCopy().data(), SIGNAL(workingCopyChanged()),
			this, SLOT(workingCopyChanged()));

	openFileInTextEditor();

	timer = new QTimer(this);
	deleteTimer = new QTimer(this);
	highlighter = new EditorHighLighting(ui->textEditorField->document());

	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

SyncableFileTextField::~SyncableFileTextField()
{
    delete ui;
}

void SyncableFileTextField::openFileInTextEditor()
{
	QFileInfo info(syncFile.data()->getFileAlias());
	QString fileExtension(info.suffix());

	if( fileExtension == "htm"  || fileExtension == "html"  || fileExtension == "tsd" ) {
		ui->textEditorField->setText("");
		ui->textEditorField->setAcceptRichText(true);
		ui->textEditorField->setHtml(*(syncFile.data()->getWorkingCopy().data()->getContent()));
	} else {
		ui->textEditorField->setAcceptRichText(false);
		ui->textEditorField->setPlainText(QString(*(syncFile.data()->getWorkingCopy().data()->getContent())));
	}
}

void SyncableFileTextField::textChanged(int position, int charsRemoved, int charsAdded )
{
	if(syncFile.data() == NULL)
		return;

	if(!patches.isEmpty()){
		if((patches.first().diffs.at(0).operation == 0 ||
		   patches.first().diffs.at(0).operation == 1) ){
			if(position == 0){
				beforeRemovedEditsEditSize = charsAdded - charsRemoved;
			}else{
				beforeRemovedEditsEditSize = 0;
			}
		}else if((patches.first().diffs.at(1).operation == 0 ||
				 patches.first().diffs.at(1).operation == 1)){
			if(position < (patches.first().start1 + patches.first().diffs.at(0).text.size())){
				beforeRemovedEditsEditSize = charsAdded - charsRemoved;
			}else{
				beforeRemovedEditsEditSize =0;
			}
		}else{
			beforeRemovedEditsEditSize = 0;
		}
	}


	//deleteTimer->stop();

	syncFile.data()->getWorkingCopy().data()->lock();
	QString *workingCopyContent = syncFile.data()->getWorkingCopy().data()->getContent();
	QString insertString = ui->textEditorField->toPlainText().mid(position, charsAdded );
	workingCopyContent->replace(position, charsRemoved, insertString);
	syncFile.data()->getWorkingCopy().data()->unlock();

}

void SyncableFileTextField::updateTextFieldToWorkingCopyContent()
{
	qDebug("ClientEditingWindow::updateTextFieldToWorkingCopyContent()");
	updateCursorPosition();
	disconnect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));


	QString temp = ui->textEditorField->toPlainText();
	patches = syncFile.data()->getWorkingCopy().data()->getPatchesToConvertString(temp);
	ui->textEditorField->setPlainText(*syncFile.data()->getWorkingCopy().data()->getContent());

	if(!patches.isEmpty()){
		EditDeleteColor();
		highlighter->setPatches(patches);
		highlighter->rehighlight();
		highlighter->clearPatches();

		connect(timer, SIGNAL(timeout()), this, SLOT(clearHighlights()));
		timer->start(2000);
	}
	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));

	getContentDiffSize();
	updateTextCursor();
	ui->textEditorField->setTextCursor(cursor);
}

void SyncableFileTextField::EditDeleteColor()
{
	//also needs some clean up
	if(!patches.isEmpty()){
		if(patches.first().diffs.count() >= 2){
			if(patches.first().diffs.at(0).operation == 1){
				deletedEdit = patches.first().diffs.first().text;
				deletedEdit.append(ui->textEditorField->toPlainText());

				startDeleteColorTimer();
			}else if(patches.first().diffs.at(1).operation == 1){
				deletedEdit = ui->textEditorField->toPlainText();
				deletedEdit.insert(patches.first().start1 +
										patches.first().diffs.first().text.size(),
										patches.first().diffs.at(1).text);
				startDeleteColorTimer();
			}
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
	if(!patches.isEmpty()){
		if(patches.first().diffs.at(0).operation == 1){
			if(ui->textEditorField->toPlainText().mid(0, patches.first().diffs.at(0).text.size()) ==
			   patches.first().diffs.at(0).text){
				temp = ui->textEditorField->toPlainText().remove(patches.first().start1, patches.first().diffs.at(0).text.size());
				ui->textEditorField->setPlainText(temp);
			}
		}else if(patches.first().diffs.at(1).operation == 1){
			if(ui->textEditorField->toPlainText().mid(patches.first().start1 + patches.first().diffs.at(0).text.size(),
													  patches.first().diffs.at(1).text.size()) == patches.first().diffs.at(1).text){
				temp = ui->textEditorField->toPlainText().remove(patches.first().start1 + patches.first().diffs.at(0).text.size() +
																 beforeRemovedEditsEditSize, patches.first().diffs.at(1).text.size());
				ui->textEditorField->setPlainText(temp);
			}
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

		if( fileExtension == "htm"  || fileExtension == "html"  || fileExtension == "tsd" ) {
			out << ui->textEditorField->toHtml();
		} else {
			out << ui->textEditorField->toPlainText();
		}

	}
}
