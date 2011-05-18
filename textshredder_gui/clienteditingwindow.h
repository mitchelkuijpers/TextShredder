#ifndef CLIENTEDITINGWINDOW_H
#define CLIENTEDITINGWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QTextCursor>
#include <QTimer>
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "syncablefile.h"
#include "clienthighlighting.h"

namespace Ui {
	class ClientEditingWindow;
}

class ClientEditingWindow : public QWidget
{
    Q_OBJECT

public:
	explicit ClientEditingWindow(QWidget *parent = 0);
	~ClientEditingWindow();

	void setWorkingCopy(WorkingCopy *);
	void startWithSocketDescriptor(int);
	void startEditingWithFile(SyncableFile *);

signals:
	void clientDisconnected();
	void fileSaved();

private slots:
	void on_disconnectButton_clicked();
	void on_saveButton_clicked();
	void textChanged( int, int, int );
	void enableEditing();
	void updateWorkingCopy();
	void updateConnectedClientsTable();
	void workingCopyChanged();

	void saveFileMe();
	void saveFile(const QString &name);
	void saveFileAs();

	void clearHighlights();
	void deleteEdits();

private:
	Ui::ClientEditingWindow *ui;
	QTcpSocket * socket;
	QString saveFilePath;
	SyncableFile *syncFile;
	void updateTextFieldToWorkingCopyContent();

	QTextCursor cursor;
	void updateTextCursor();
	void getContentDiffSize();
	void updateCursorPosition();

	QTimer * timer;
	QTimer * deleteTimer;

	int oldEditWindowSize;
	int diffSize;
	int cursorPosition;
	QString beforeCursorText;
	QString afterCursorText;

	QString deletedEditFirst;
	QList<Patch> Patches;
	void EditDeleteColor();
	void startDeleteColorTimer();
	ClientHighlighting * highlighter;
};

#endif // CLIENTEDITINGWINDOW_H
