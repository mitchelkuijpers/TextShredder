#ifndef SERVERCONTROLVIEW_H
#define SERVERCONTROLVIEW_H

#include <QWidget>
#include "server.h"
#include <QFileDialog>
#include <QFile>
#include <QChar>
namespace Ui {
	class ServerControlView;
}

class ServerControlView : public QWidget
{
    Q_OBJECT

public:
	explicit ServerControlView(QWidget *parent = 0);
	~ServerControlView();

private slots:
	void on_fileSelectButton_clicked();
	void on_startButton_clicked();
	void on_stopButton_clicked();

private:
	Ui::ServerControlView *ui;
	Server *server;

protected:
	void readSelectedFile();
	QString openedFilePath;
	QByteArray fileContent;
};

#endif // SERVERCONTROLVIEW_H