#ifndef CLIENTCONTROLVIEW_H
#define CLIENTCONTROLVIEW_H

#include <QWidget>
#include <QTcpSocket>
#include "syncablefile.h"

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
	void receivedDownload(TextShredderPacket &);
	void connectionStateChanged(TextShredderConnectionStatus status);

private:
	Ui::ClientControlView *ui;
	TextShredderConnection *connection;
	SyncableFile *syncFile;
};

#endif // CLIENTCONTROLVIEW_H
