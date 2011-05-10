#include <QtGui/QApplication>
#include "mainwindow.h"
#include "editorview.h"
#include "debugview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//MainWindow w;
	//w.show();

	//EditorView e;
	//e.show();

	DebugView d;
	d.show();

    return a.exec();
}
