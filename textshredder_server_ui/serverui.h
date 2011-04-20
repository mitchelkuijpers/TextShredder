#ifndef SERVERUI_H
#define SERVERUI_H
#define PORTNUMBER 1027

#include <QMainWindow>
#include <QTcpServer>
#include "../textshredder_gui/server.h"

namespace Ui {
    class ServerUI;
}

class ServerUI : public QTcpSocket
{
    Q_OBJECT

public:
    explicit ServerUI(QWidget *parent = 0);
    ~ServerUI();
	void startServerWithDefaultFileContentsAndPort();

private:
    Ui::ServerUI *ui;
	QByteArray fileContent;
	Server * server;

};

#endif // SERVERUI_H
