#include <QtGui/QApplication>
#include "mainwindow.h"
#include "editorview.h"
#include "debugview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	DebugView d;
	d.show();

	MainWindow w;
	w.show();

	EditorView e;
	e.show();

    return a.exec();
}
