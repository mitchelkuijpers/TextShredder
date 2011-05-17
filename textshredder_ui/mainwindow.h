#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editorview.h"

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
	void animationMoveTo(QWidget * target, QRect startRect, QRect endRect, int animationLength );
	void performTextSlideInAnimation();

	/**
	  * The function builds up a QStringList and fills it with some fonts.
	  * A for loop looks in the :ui/core/fonts folder
	  * and shows an error if the font cannot be opened.
	  */
	void setDefaultFont();
	void functionToExecute();

private:
    Ui::MainWindow *ui;
	EditorView editorView;
private slots:
 void on_connectButton_clicked();
 void on_cancelButton_clicked();
 void on_isServerInput_clicked();
};

#endif // MAINWINDOW_H
