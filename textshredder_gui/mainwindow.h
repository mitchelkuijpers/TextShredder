#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "syncablefile.h"

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
	void clientConnected(int);
	void fileStarted(SyncableFile *);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
