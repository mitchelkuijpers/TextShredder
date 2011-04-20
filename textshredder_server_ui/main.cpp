#include <QtGui/QApplication>
#include "serverui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerUI w;
    w.show();



    return a.exec();
}
