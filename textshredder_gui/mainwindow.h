#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "syncablefile.h"
#include "textshredderlogging.h"




namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void serverDidStart();
	void editingDisconnected();
	void fileStarted(SyncableFile *);

	/**
	  * Function that will update the available files table in the GUI
	  */
	void updateAvailableFiles();



private:
    Ui::MainWindow *ui;
    TextShredderLogging *log;
    TextShredderLogging *testlog;
};

#endif // MAINWINDOW_H
