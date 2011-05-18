#include "editorview.h"
#include "ui_editorview.h"
#include "textfield.h"
#include "../textshredder_core/libraries/synchronization/filemanager.h"

EditorView::EditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorView)
{
	ui->setupUi(this);
	ui->fileTreeWidget->setFocus();
	setFileTreeWidgetColumnsInModel();

	connect(FileManager::Instance(), SIGNAL(availableFilesChanged()), this, SLOT(rebuildSharedFilesListTreeView));
}

EditorView::~EditorView()
{
    delete ui;
}

void EditorView::on_addFileButton_clicked()
{
	QFileDialog Qfd;
	openedFilePath = Qfd.getOpenFileName(this, tr("TextShredder File Selector"), QDir::currentPath(), QString("*.txt"));

	if ( !openedFilePath.isEmpty() ) {
		addFileToFileTreeWidget( openedFilePath );
	}
}

void EditorView::on_addFolderButton_clicked()
{
	QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		  "",
		 QFileDialog::ShowDirsOnly
		 | QFileDialog::DontResolveSymlinks);

	if ( !directoryPath.isEmpty() ) {
		addFolderToFileTreeWidget( directoryPath );
	}
}

void EditorView::setFileTreeWidgetColumnsInModel()
{
	model.setHorizontalHeaderItem(0, new QStandardItem( "Files" ));
	model.setHorizontalHeaderItem(1, new QStandardItem( "Status" ));
}

void EditorView::addFileToFileTreeWidget( QString filePath )
{
	FileManager::Instance()->addFileWithPath(filePath);
	qDebug() << filePath;
}

void EditorView::addFolderToFileTreeWidget( QString directoryPath )
{
	QDir dir;
	dir.setPath(directoryPath);
	QStringList filters("*.txt");
	QStringList list = dir.entryList(filters);

	int i = 0;
	for(i = 0; i < list.count(); i++ ) {
		QString fileName = list.at(i);
		QString absolutePath(directoryPath + "/" + fileName);
		FileManager::Instance()->addFileWithPath(absolutePath);
	}
}


void EditorView::rebuildSharedFilesListTreeView()
{


//	QDir dir;
//	QStringList filters("*.txt");
//	QStringList list = dir.entryList(filters);

//	int rowCount = model.rowCount();

//	int i = 0;
//	for(i = 0; i < list.count(); i++ ) {
//		QString filePath = list.at(i);
//		FileManager::Instance()->addFileWithPath(filePath);

//		QStandardItem *item = new QStandardItem( filePath );
//		item->setEditable( false );
//		item->setCheckable( true );
//		model.setItem(rowCount, 0, item);

//		QStandardItem *status = new QStandardItem( QString("NS") );
//		model.setItem(rowCount, 1, status);

//		rowCount++;
//	}

//	ui->fileTreeWidget->setModel(&model);
}


void EditorView::on_fileTreeWidget_clicked(QModelIndex index)
{
	//Check if row is checked. If so, add it to the FileManager
	//If row is unchecked, remove it from the FileManager
}

void EditorView::on_fileTreeWidget_doubleClicked(QModelIndex index)
{
	//You can't open a file twice! -> Not implemented yet
	const QAbstractItemModel * mod = index.model();
	QString fileName = mod->data(mod->index(index.row(), 0), Qt::DisplayRole).toString();
	openFileInEditor( fileName );
}

void EditorView::on_openedFileTabs_tabCloseRequested(int index)
{
	ui->openedFileTabs->removeTab(index);
}

void EditorView::openFileInEditor( QString fileName )
{
	TextField *textfield = new TextField(this);
	ui->openedFileTabs->addTab(textfield, fileName);
}

void EditorView::setToServerMode()
{
	qDebug("TODO: EditorView::setToServerMode");
}

void EditorView::setToClientMode()
{
	qDebug("TODO: EditorView::setToClientMode");
}
