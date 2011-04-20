#include "clienteditingwindow.h"
#include "ui_clienteditingwindow.h"

ClientEditingWindow::ClientEditingWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ClientEditingWindow), workingCopy(NULL)
{
    ui->setupUi(this);

	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}

ClientEditingWindow::~ClientEditingWindow()
{
    delete ui;
}

void ClientEditingWindow::setWorkingCopy(WorkingCopy *copy)
{
	disconnect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
	workingCopy = copy;
	ui->textEdit->setPlainText(*(workingCopy->getContent()));

	connect(ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)),
			this, SLOT(textChanged(int, int, int)));
}


void ClientEditingWindow::textChanged(int position, int charsRemoved, int charsAdded )
{
	if(workingCopy == NULL)
		return;

	workingCopy->lock();
	QString *workingCopyContent = workingCopy->getContent();
	QString insertString = ui->textEdit->toPlainText().mid(position, charsAdded );
	workingCopyContent->replace(position, charsRemoved, insertString);
	workingCopy->unlock();

	qDebug("\n");
	qDebug() << *(workingCopy->getContent());
}

void ClientEditingWindow::on_disconnectButton_clicked()
{
	clientDisconnected();
}

void ClientEditingWindow::startWithSocketDescriptor(int socketDescriptor)
{
	ui->textEdit->setEnabled(false);
	workingCopy = new WorkingCopy(this);
	SyncThread * thread = new SyncThread(this, socketDescriptor, *workingCopy,
										 false);
	connect(thread, SIGNAL(downloadFinished()), this, SLOT(enableEditing()));
	thread->start();
}

void ClientEditingWindow::enableEditing()
{
	ui->textEdit->setEnabled(true);
	qDebug() << workingCopy->getContent();
	ui->textEdit->setPlainText(*workingCopy->getContent());
}
