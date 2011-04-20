#ifndef CLIENTCONTROLVIEW_H
#define CLIENTCONTROLVIEW_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
	class ClientControlView;
}

class ClientControlView : public QWidget
{
    Q_OBJECT

public:
	explicit ClientControlView(QWidget *parent = 0);
	~ClientControlView();

signals:
	void connectedToHost(int);
private slots:

	void on_connectButton_clicked();

private:
	Ui::ClientControlView *ui;
};

#endif // CLIENTCONTROLVIEW_H
