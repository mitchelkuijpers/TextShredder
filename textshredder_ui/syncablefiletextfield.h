#ifndef SYNCABLEFILETEXTFIELD_H
#define SYNCABLEFILETEXTFIELD_H

#define CURSORUPDATESIZE 3

#include <QWidget>
#include <QTextCursor>
#include "../textshredder_core/libraries/synchronization/models/syncablefile.h"

namespace Ui {
	class SyncableFileTextField;
}

class SyncableFileTextField : public QWidget
{
    Q_OBJECT

public:
	SyncableFileTextField(QWidget *parent, QSharedPointer<SyncableFile> file);
	~SyncableFileTextField();

private:
	void updateTextFieldToWorkingCopyContent();
	Ui::SyncableFileTextField *ui;
	SyncableFile *syncFile;

	QTextCursor cursor;
	void updateTextCursor();
	void getContentDiffSize();
	void updateCursorPosition();

	int oldEditWindowSize;
	int diffSize;
	int cursorPosition;
	QString beforeCursorText;
	QString afterCursorText;

private slots:
	void textChanged(int position, int charsRemoved, int charsAdded );
};

#endif // TEXTFIELD_H
