#ifndef SERVERTABWINDOW_H
#define SERVERTABWINDOW_H

#include <QWidget>
#include "server.h"
#include <QFileDialog>
#include <QFile>
#include <QChar>
namespace Ui {
    class ServerTabWindow;
}

class ServerTabWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerTabWindow(QWidget *parent = 0);
    ~ServerTabWindow();

private slots:
	void on_fileSelectButton_clicked();
	void on_startButton_clicked();

    void on_stopButton_clicked();
	void readInputFile();

private:
    Ui::ServerTabWindow *ui;
    Server server;
protected:
	QString openedFilePath;
	void sendFileContentToClient(QString fileContent);
};

#endif // SERVERTABWINDOW_H
