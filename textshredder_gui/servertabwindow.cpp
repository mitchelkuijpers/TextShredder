#include "servertabwindow.h"
#include "ui_servertabwindow.h"

ServerTabWindow::ServerTabWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerTabWindow)
{
    ui->setupUi(this);
}

ServerTabWindow::~ServerTabWindow()
{
    delete ui;
}

void ServerTabWindow::on_startButton_clicked()
{
    int portNumber = ui->portSpinBox->text().toInt();
    if(!server.listen(QHostAddress::Any, portNumber)) {
        qDebug("Could not start the server");
    }
    ui->stopButton->setEnabled(1);
    ui->startButton->setEnabled(0);
}

void ServerTabWindow::on_stopButton_clicked()
{
    server.close();
    ui->stopButton->setEnabled(0);
    ui->startButton->setEnabled(1);
}
