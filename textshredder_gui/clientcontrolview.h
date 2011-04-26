#ifndef CLIENTCONTROLVIEW_H
#define CLIENTCONTROLVIEW_H

#include <QWidget>
#include <QTcpSocket>

#include "../textshredder_synchronization_lib/textshredderconnection.h"

namespace Ui {
	class ClientControlView;
}

class ClientControlView : public QWidget
{
    Q_OBJECT

public:
	explicit ClientControlView(QWidget *parent = 0);
	~ClientControlView();
	QTcpSocket *socket;
signals:
	void connectedToHost(int);
private slots:

	void on_connectButton_clicked();

private:
	Ui::ClientControlView *ui;
	TextShredderConnection *connection;
};

#endif // CLIENTCONTROLVIEW_H
