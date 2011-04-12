#ifndef CLIENTACTIVEWINDOW_H
#define CLIENTACTIVEWINDOW_H

#include <QWidget>

namespace Ui {
    class ClientActiveWindow;
}

class ClientActiveWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientActiveWindow(QWidget *parent = 0);
    ~ClientActiveWindow();

private:
    Ui::ClientActiveWindow *ui;
};

#endif // CLIENTACTIVEWINDOW_H
