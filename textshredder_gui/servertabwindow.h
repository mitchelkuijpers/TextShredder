#ifndef SERVERTABWINDOW_H
#define SERVERTABWINDOW_H

#include <QWidget>
#include "server.h"

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
    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::ServerTabWindow *ui;
    Server server;
};

#endif // SERVERTABWINDOW_H
