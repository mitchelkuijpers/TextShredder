#include "syncablefiletextfield.h"
#include "ui_syncablefiletextfield.h"
#include <QFileDialog>
#include "../textshredder_core/libraries/notification/notificationmanager.h"

SyncableFileTextField::SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file) :
    QWidget(parent),
	ui(new Ui::SyncableFileTextField),
	highlightingOn(true)
{
    ui->setupUi(this);

	syncFile = file;
	connect(syncFile.data()->getWorkingCopy().data(), SIGNAL(workingCopyChanged()),
			this, SLOT(workingCopyChanged()));
	connect(syncFile.data(), SIGNAL(fileShouldNotifyEndOfSharing()), this, SLOT(showEndSharingNotification()));

	openFileInTextEditor();

	timer = new QTimer(this);
	deleteTimer = new QTimer(this);
	highlighter = new EditorHighLighting(ui->textEditorField->document());

	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

SyncableFileTextField::~SyncableFileTextField()
{
	syncFile.data()->close();
    delete ui;
}

void SyncableFileTextField::openFileInTextEditor()
{
	QFileInfo info(syncFile.data()->getFileAlias());
	fileExtension = info.suffix();

	if( fileExtension == "htm"  || fileExtension == "html"  || fileExtension == "tsd" ) {
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
	qDebug() << "cursorPosition: " << cursorPosition;
	disconnect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));

	QString temp = ui->textEditorField->toPlainText();
	patches = syncFile.data()->getWorkingCopy().data()->getPatchesToConvertString(temp);
	qDebug() << patches.first().toString();
//	if(temp.size() > 100000){
//		highlightingOn = false;
//	}else{
//		highlightingOn = true;
//	}


	if( fileExtension == "htm"  || fileExtension == "html"  || fileExtension == "tsd" ) {
		ui->textEditorField->setHtml(*syncFile.data()->getWorkingCopy().data()->getContent());
	} else {
		ui->textEditorField->setPlainText(*syncFile.data()->getWorkingCopy().data()->getContent());
	}

	updateTextCursor();
	if(!patches.isEmpty() && highlightingOn == true){
		EditDeleteColor();
		highlighter->setPatches(patches);
		highlighter->rehighlight();
		highlighter->clearPatches();
		connect(timer, SIGNAL(timeout()), this, SLOT(clearHighlights()));
		timer->start(2000);
	}

	connect(ui->textEditorField->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));

}

void SyncableFileTextField::setCPPHighlighting(bool cppHighlighting)
{
	highlighter->setcppHighlighting(cppHighlighting);
}

void SyncableFileTextField::EditDeleteColor()
{
	if(!patches.isEmpty()){
		int beforeDiffSize =0;
		bool deletes = false;
		for(int i=0; i<patches.first().diffs.count(); i++){
			if(patches.first().diffs.at(i).operation == 1){
				deletedEdit = ui->textEditorField->toPlainText();
				deletedEdit.insert(patches.first().start1 + beforeDiffSize,
										patches.first().diffs.at(i).text);


				if( fileExtension == "htm"  || fileExtension == "html"  || fileExtension == "tsd" ) {
					ui->textEditorField->setHtml(deletedEdit);
				} else {
					ui->textEditorField->setPlainText(deletedEdit);
				}
				lockCursorPostion();

				deletes =true;
			}
			beforeDiffSize += patches.first().diffs.at(i).text.size();
		}
		if(deletes){
			startDeleteColorTimer();
		}
	}
}

void SyncableFileTextField::startDeleteColorTimer()
{
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
	int patchSize = 0;

	if(!patches.isEmpty()){
		for(int i=0; i<patches.first().diffs.count(); i++){
			if(patches.first().diffs.at(i).operation == 1){
				temp = ui->textEditorField->toPlainText();
				temp.remove(patches.first().start1 + patchSize, patches.first().diffs.at(i).text.size());
				patchSize -= patches.first().diffs.at(i).text.size();

				if( fileExtension == "htm"  || fileExtension == "html"  || fileExtension == "tsd" ) {
					ui->textEditorField->setHtml(temp);
				} else {
					ui->textEditorField->setPlainText(temp);
				}
				cursor.setPosition(cursorPosition);
				qDebug() << "fuck cursor: " << cursorPosition;
				ui->textEditorField->setTextCursor(cursor);

			}else{
				patchSize += patches.first().diffs.at(i).text.size();
			}
		}

		patches.clear();
		qDebug() << "patches cleared";
	}
}

void SyncableFileTextField::updateTextCursor()
{

	if(!patches.isEmpty()){

		int prevDiffSize = patches.first().start1;
		if(prevDiffSize >= cursorPosition){
			lockCursorPostion();
		}else{
			for(int i=0; prevDiffSize < cursorPosition && i<patches.first().diffs.count(); i++){
				if(patches.first().diffs.at(i).operation == 0){
					cursorPosition += patches.first().diffs.at(i).text.size();
					cursor.setPosition(cursorPosition, QTextCursor::MoveAnchor);
					ui->textEditorField->setTextCursor(cursor);
				}else if(patches.first().diffs.at(i).operation == 1){
					lockCursorPostion();
					cursorPosition -= patches.first().diffs.at(i).text.size();
				}
				prevDiffSize += patches.first().diffs.at(i).text.size();
			}
		}
	}

}

void SyncableFileTextField::updateCursorPosition()
{
	cursor = ui->textEditorField->textCursor();
	cursorPosition = cursor.position();
	oldCursorPosition = cursorPosition;
	qDebug() << "cursorPos: " << cursor.position();
}

void SyncableFileTextField::lockCursorPostion()
{
	cursor.setPosition(oldCursorPosition);
	ui->textEditorField->setTextCursor(cursor);
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

void SyncableFileTextField::showEndSharingNotification()
{
	QString message("The server stopped sharing the following file: \n");
	message.append(" - ");
	message.append(syncFile.data()->getFileAlias());
	message.append("\n\nYour edits will not be synced anymore.\nYou can still save this file locally.");
	Notification notification(this, message, NotificationTypeWARNING);
	NotificationManager::Instance()->createNotificationDialog(notification);
}
