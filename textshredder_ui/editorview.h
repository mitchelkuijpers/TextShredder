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
#include "../textshredder_core/libraries/synchronization/filemanager.h"
#include "syncablefiletextfield.h"
#include "../textshredder_core/libraries/performance/performancecalculator.h"

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
	void openFileInEditor( QSharedPointer<SyncableFile> file );

	void setToServerMode();
	void setToClientMode();
	void setColumnWidths();

private:
	Ui::EditorView *ui;
	QStandardItemModel model;
	bool isServer;
	QList< QSharedPointer<SyncableFileTextField> > openedFilesList;
	QSharedPointer<SyncableFileTextField> textfield;

	void addCheckBoxToSharedFilesListTreeView( int row, SyncableFile * syncableFile );
	void addFileNameToSharedFilesListTreeView( int row, SyncableFile * syncableFile );
	void addStatusIconToSharedFilesListTreeView( int row, SyncableFile * syncableFile );
	void setServerStatusIcons(SyncableFile * syncableFile, QStandardItem *status);
	void setClientStatusIcons(SyncableFile * syncableFile, QStandardItem *status);

private slots:
 void on_showModificationsInput_toggled(bool checked);
 void on_syntaxHighightingCPPInput_toggled(bool checked);
 void on_syntaxHighlightingOffInput_toggled(bool checked);
 void on_fileTreeWidget_doubleClicked(QModelIndex index);
 void on_openedFileTabs_tabCloseRequested(int index);
 void on_fileTreeWidget_clicked(QModelIndex index);
 void on_addFolderButton_clicked();
 void on_addFileButton_clicked();
 void rebuildSharedFilesListTreeView();
 void updateAveragePerformance(float);
 void updateAveragePerformancePercentage(float);
};

#endif // EDITORVIEW_H
