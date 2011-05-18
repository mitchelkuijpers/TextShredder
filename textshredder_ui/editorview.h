#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTreeView>
#include <QStandardItemModel>
#include <QtCore/QDebug>
#include <QTreeWidgetItem>
#include <QResource>

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
	void openFileInEditor( QString fileName );

	void setToServerMode();
	void setToClientMode();

private:
	Ui::EditorView *ui;
	QStandardItemModel model;
	bool isServer;

private slots:
 void on_fileTreeWidget_doubleClicked(QModelIndex index);
 void on_openedFileTabs_tabCloseRequested(int index);
 void on_fileTreeWidget_clicked(QModelIndex index);
 void on_addFolderButton_clicked();
 void on_addFileButton_clicked();
 void rebuildSharedFilesListTreeView();

};

#endif // EDITORVIEW_H
