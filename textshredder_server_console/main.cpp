#include <QtCore/QCoreApplication>
#include <QTcpServer>
#include "../textshredder_gui/server.h"
#include "../textshredder_synchronization_lib/workingcopy.h"

#define PORTNUMBER 1027

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	startServerWithDefaultFileContentsAndPort();

    return a.exec();
}

void startServerWithDefaultFileContentsAndPort()
{
	QByteArray * fileContent = "This is nice file content!\nHaha";

	if( !server->listenWithFile( QHostAddress::Any, PORTNUMBER, &fileContent ) ) {
		qDebug("Could not start the server");
	}
}
