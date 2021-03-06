#ifndef SYNCABLEFILETEXTFIELD_H
#define SYNCABLEFILETEXTFIELD_H

#define CURSORUPDATESIZE 3

#include <QWidget>
#include <QTextCursor>
#include <QTimer>
#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"
#include "../textshredder_core/libraries/diff_match_patch/diff_match_patch.h"
#include "editorhighlighting.h"

namespace Ui {
	class SyncableFileTextField;
}

class SyncableFileTextField : public QWidget
{
    Q_OBJECT

public:
	SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file);
	~SyncableFileTextField();

	void setCPPHighlighting(bool cppHighlighting);
	void setModificationHighlighting(bool modificationHighlighting);

private:
	void updateTextFieldToWorkingCopyContent();
	void openFileInTextEditor();

	Ui::SyncableFileTextField *ui;
	QSharedPointer<SyncableFile> syncFile;

	QTextCursor cursor;
	void updateTextCursor();
	void getContentDiffSize();
	void updateCursorPosition();

	QString fileExtension;


	int cursorPosition;
	int oldCursorPosition;
	void lockCursorPostion();

	QTimer * timer;
	QTimer * deleteTimer;
	QString deletedEdit;
	QList<Patch> patches;
	void EditDeleteColor();
	void startDeleteColorTimer();
	EditorHighLighting * highlighter;

	void removeDeletes();
	bool highlightingOn;


private slots:
	void on_saveFileButton_clicked();
	void textChanged(int position, int charsRemoved, int charsAdded );
	void workingCopyChanged();
	void showEndSharingNotification();

	void clearHighlights();
	void deleteEdits();


};

#endif // TEXTFIELD_H
