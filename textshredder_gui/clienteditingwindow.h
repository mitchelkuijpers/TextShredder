#ifndef CLIENTEDITINGWINDOW_H
#define CLIENTEDITINGWINDOW_H

#include <QWidget>
#include "../textshredder_synchronization_lib/workingcopy.h"
#include "../textshredder_synchronization_lib/syncthread.h"

namespace Ui {
	class ClientEditingWindow;
}

class ClientEditingWindow : public QWidget
{
    Q_OBJECT

public:
	explicit ClientEditingWindow(QWidget *parent = 0);
	~ClientEditingWindow();

	void setWorkingCopy(WorkingCopy *);
	void startWithSocketDescriptor(int);

signals:
	void clientDisconnected();

private slots:
	void on_disconnectButton_clicked();
	void textChanged( int, int, int );

private:
	Ui::ClientEditingWindow *ui;

	WorkingCopy *workingCopy;
};

#endif // CLIENTEDITINGWINDOW_H
