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

private slots:
	void on_connectButton_clicked();

	/**
	  * Function that will be fired when the TextShredderConnection received
	  * a file donwload packet.
	  *
	  * @param the packet that is received.
	  */
	void receivedDownload(TextShredderPacket &);

	/**
	  * Function that will be fired when the TextShredderConnection status
	  * changes.
	  *
	  * @param the new status of the connection.
	  */
	void connectionStateChanged(TextShredderConnectionStatus status);

private:
	/**
	  * Makes a new SyncFile object and removes the existing one.
	  */
	void makeNewSyncFile();

	/**
	  * Makes a new TextShredderConnection object, connects the signals and
	  * stores it in the connection variable.
	  * It will disconnect and delete the previous connection if it exists.
	  */
	void makeNewConnection(QString &hostname, int port);

	Ui::ClientControlView *ui;
	TextShredderConnection *connection;
	SyncableFile *syncFile;
};

#endif // CLIENTCONTROLVIEW_H
