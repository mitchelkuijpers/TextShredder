#include "clientcontrolview.h"
#include "ui_clientcontrolview.h"
#include "filemanager.h"


ClientControlView::ClientControlView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ClientControlView),  connection(NULL), syncFile(NULL)
{
    ui->setupUi(this);
}

ClientControlView::~ClientControlView()
{
    delete ui;
}


void ClientControlView::on_connectButton_clicked()
{
	QString portText(ui->portSpinner->text());
	QString hostname(ui->serverAdressLineEdit->text());
	int port = portText.toInt();

	makeNewSyncFile();
	makeNewConnection(hostname, port);
}

void ClientControlView::makeNewSyncFile()
{
	if (syncFile != NULL) {
		FileManager::Instance()->removeFile (syncFile);
		syncFile = NULL;
	}
	syncFile = new SyncableFile(this);
	FileManager::Instance()->addSyncFile(syncFile);
}

void ClientControlView::makeNewConnection(QString &hostname, int port)
{
	if (connection != NULL) {
		disconnect(connection,SIGNAL(newIncomingPacket(TextShredderPacket &)),
				this, SLOT(receivedDownload(TextShredderPacket &)));
		disconnect(connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
				 this, SLOT(connectionStateChanged(TextShredderConnectionStatus)));
		delete connection;
	}
	connection = new TextShredderConnection(this, hostname, port);
	connect(connection,SIGNAL(newIncomingPacket(TextShredderPacket &)),
			this, SLOT(receivedDownload(TextShredderPacket &)));
	connect (connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
			 this, SLOT(connectionStateChanged(TextShredderConnectionStatus)));
}

void ClientControlView::receivedDownload(TextShredderPacket &packet)
{
	QString contentString(packet.getContent());
	qDebug() << contentString;
	syncFile->getWorkingCopy ()->setContent(contentString);
}

void ClientControlView::connectionStateChanged(TextShredderConnectionStatus status) {
	if (status == Neutral) {
		QByteArray emptyContent;
		TextShredderPacket packet(this, kPacketTypeFileRequest, emptyContent);
		connection->write(packet);
	}
}
