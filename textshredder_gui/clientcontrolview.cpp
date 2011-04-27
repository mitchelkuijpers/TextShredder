#include "clientcontrolview.h"
#include "ui_clientcontrolview.h"
#include "filemanager.h"


ClientControlView::ClientControlView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ClientControlView),  connection(NULL), syncFile(NULL),
	syncThread(NULL)
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
		disconnect(connection,SIGNAL(incomingFileDataPacketContent(QByteArray&)),
				this, SLOT(receivedDownload(QByteArray &)));
		disconnect(connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
				 this, SLOT(connectionStateChanged(TextShredderConnectionStatus)));
		delete connection;
	}
	connection = new TextShredderConnection(this, hostname, port);
	connect(connection,SIGNAL(incomingFileDataPacketContent(QByteArray&)),
			this, SLOT(receivedDownload(QByteArray &)));
	connect (connection, SIGNAL(statusChanged(TextShredderConnectionStatus)),
			 this, SLOT(connectionStateChanged(TextShredderConnectionStatus)));
	ui->setAliasButton->setEnabled(true);
}

void ClientControlView::closeConnection()
{
	ui->setAliasButton->setEnabled(false);
	delete connection;
}

void ClientControlView::receivedDownload(QByteArray &content)
{
	QString contentString(content);
	syncFile->getWorkingCopy ()->setContent(contentString);
	startSyncThread();
}

void ClientControlView::connectionStateChanged(TextShredderConnectionStatus status) {
	if (status == Neutral) {
		this->askForDownload();
	}
}

void ClientControlView::askForDownload()
{
	QByteArray emptyContent;
	TextShredderPacket packet(this, kPacketTypeFileRequest, emptyContent);
	connection->write(packet);
}

void ClientControlView::startSyncThread()
{
	disconnect(connection, SIGNAL(newIncomingPacket(TextShredderPacket&)),
			   this, SLOT(receivedDownload(TextShredderPacket&)));
	syncThread = new SyncThread(this, *connection, *(syncFile->getWorkingCopy()));
}

void ClientControlView::closeCurrentConnection()
{
	syncThread->stop();
	syncThread->deleteLater();
}

void ClientControlView::on_setAliasButton_clicked()
{
	if (ui->aliasLineEdit->text().length () > 0 ) {
		QString newAliasString = ui->aliasLineEdit->text();
		QByteArray newAlias;
		newAlias.append (newAliasString);
		TextShredderPacket packet(this, kPacketTypeSetAlias, newAlias);
		connection->write(packet);
	}
}
