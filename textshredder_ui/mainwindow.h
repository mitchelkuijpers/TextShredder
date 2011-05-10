#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void changeWindowStateToServer();
	void changeWindowStateToClient();
	void animationMoveTo(QObject * target, QRect startRect, QRect endRect, int animationLength );
	void performStarupAnimation();

private:
    Ui::MainWindow *ui;

private slots:
 void on_cancelButton_clicked();
 void on_isServerInput_clicked();
};

#endif // MAINWINDOW_H
