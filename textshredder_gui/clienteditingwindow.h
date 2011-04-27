#ifndef CLIENTEDITINGWINDOW_H
#define CLIENTEDITINGWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "../textshredder_synchronization_lib/syncthread.h"
#include "syncablefile.h"

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

private:
	Ui::ClientEditingWindow *ui;
	QTcpSocket * socket;
	QString saveFilePath;
	SyncableFile *syncFile;
	void updateTextFieldToWorkingCopyContent();
};

#endif // CLIENTEDITINGWINDOW_H
