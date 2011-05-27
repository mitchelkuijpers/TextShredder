#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editorview.h"
#include "../textshredder_core/client/client.h"
#include <qfile.h>
#include <qtextstream.h>

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
	void saveSettings();
	/**
	  * The function builds up a QStringList and fills it with some fonts.
	  * A for loop looks in the :ui/core/fonts folder
	  * and shows an error if the font cannot be opened.
	  */
	void setDefaultFont();
	void displayErrorNotification(QAbstractSocket::SocketError error);

private:
	Ui::MainWindow *ui;
	EditorView editorView;

	bool validateAliasInput();

private slots:
	void on_aliasInput_textChanged(QString );
	void on_connectButton_clicked();
	void on_cancelButton_clicked();
	void on_isServerInput_clicked();
	void clientDidConnect();
	void clientHadError(QAbstractSocket::SocketError error);
};

#endif // MAINWINDOW_H
