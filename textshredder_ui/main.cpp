#include <QtGui/QApplication>
#include "mainwindow.h"
#include "editorview.h"
#include "debugview.h"
#include <QFontDatabase>
#include <QMessageBox>

void setDefaultFont();
void openEditorView();
void openDebugView();
QList<QPushButton*> buttons;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	setDefaultFont();

	//EditorView e;
	//e.show();
	MainWindow w;
	w.show();

	return a.exec();
}

void openEditorView()
{
	EditorView e;
	e.show();
}

void openDebugView()
{
	DebugView d;
	d.show();
}

void setDefaultFont()
{
	QStringList list;
	list << "Cantarell-Bold.ttf" << "Cantarell-BoldOblique.ttf" << "Cantarell-Oblique.ttf" << "Cantarell-Regular.ttf";
	int fontID(-1);
	bool fontWarningShown(false);
	for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
		QFile res(":/ui/core/fonts/" + *constIterator);
		if (res.open(QIODevice::ReadOnly) == false) {
			if (fontWarningShown == false) {
				QMessageBox::warning(0, "Application", (QString)" Cannot open font " + QChar(0x00AB) + " Cantarell " + QChar(0x00BB) + ".");
				fontWarningShown = true;
			}
		} else {
			fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
			if (fontID == -1 && fontWarningShown == false) {
				QMessageBox::warning(0, "Application", (QString)" Cannot open font " + QChar(0x00AB) + " Cantarell " + QChar(0x00BB) + ".");
				fontWarningShown = true;
			}
		}
	}
}
