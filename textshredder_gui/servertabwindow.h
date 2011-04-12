#ifndef SERVERTABWINDOW_H
#define SERVERTABWINDOW_H

#include <QWidget>

namespace Ui {
    class ServerTabWindow;
}

class ServerTabWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerTabWindow(QWidget *parent = 0);
    ~ServerTabWindow();

private:
    Ui::ServerTabWindow *ui;
};

#endif // SERVERTABWINDOW_H
