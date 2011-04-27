#ifndef CLIENTCONTROLVIEW_H
#define CLIENTCONTROLVIEW_H

#include <QWidget>
#include <QTcpSocket>
#include "syncablefile.h"

#include "../textshredder_synchronization_lib/textshredderconnection.h"
#include "../textshredder_synchronization_lib/syncthread.h"

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
	void closeConnection();

private slots:
	void on_setAliasButton_clicked();
	void on_connectButton_clicked();

	/**
	  * Function that will be fired when the TextShredderConnection received
	  * a file donwload packet.
	  *
	  * @param the packet that is received.
	  */
	void receivedDownload(QByteArray &content);

	/**
	  * Function that will be fired when the TextShredderConnection status
	  * changes.
	  *
	  * @param the new status of the connection.
	  */
	void connectionStateChanged(TextShredderConnectionStatus status);

	void closeCurrentConnection();

private:
	/**
	  * Will send a File Download request on the TextShredderConnection
	  * instance.
	  */
	void askForDownload();

	/**
	  * Will start a new SyncThread object and stops the existing one.
	  */
	void startSyncThread();
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
	SyncThread *syncThread;
};

#endif // CLIENTCONTROLVIEW_H
