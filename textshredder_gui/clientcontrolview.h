#ifndef CLIENTCONTROLVIEW_H
#define CLIENTCONTROLVIEW_H

#include <QWidget>

namespace Ui {
	class ClientControlView;
}

class ClientControlView : public QWidget
{
    Q_OBJECT

public:
	explicit ClientControlView(QWidget *parent = 0);
	~ClientControlView();

private slots:

private:
	Ui::ClientControlView *ui;
};

#endif // CLIENTCONTROLVIEW_H
