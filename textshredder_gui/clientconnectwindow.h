#ifndef CLIENTCONNECTWINDOW_H
#define CLIENTCONNECTWINDOW_H

#include <QWidget>

namespace Ui {
    class ClientConnectWindow;
}

class ClientConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientConnectWindow(QWidget *parent = 0);
    ~ClientConnectWindow();

private slots:

    void on_clientConnectButton_clicked();

private:
    Ui::ClientConnectWindow *ui;
};

#endif // CLIENTCONNECTWINDOW_H
