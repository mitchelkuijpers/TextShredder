#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTreeView>
#include <QStandardItemModel>

namespace Ui {
    class EditorView;
}

class EditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorView(QWidget *parent = 0);
    ~EditorView();
	void setModel();
	void setFileTreeWidgetColumnsInModel();
	void addFileToFileTreeWidget( QString fileName );
	void addFolderToFileTreeWidget( QString folderName );

private:
    Ui::EditorView *ui;
	QString openedFilePath;
	QStandardItemModel model;

private slots:
 void on_fileTreeWidget_clicked(QModelIndex index);
 void on_addFolderButton_clicked();
 void on_addFileButton_clicked();
};

#endif // EDITORVIEW_H
