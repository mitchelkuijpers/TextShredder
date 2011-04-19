#ifndef CLIENTEDITINGWINDOW_H
#define CLIENTEDITINGWINDOW_H

#include <QWidget>

namespace Ui {
	class ClientEditingWindow;
}

class ClientEditingWindow : public QWidget
{
    Q_OBJECT

public:
	explicit ClientEditingWindow(QWidget *parent = 0);
	~ClientEditingWindow();

private:
	Ui::ClientEditingWindow *ui;
};

#endif // CLIENTEDITINGWINDOW_H
