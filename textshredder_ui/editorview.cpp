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
}

EditorView::~EditorView()
{
    delete ui;
}

void EditorView::on_addFileButton_clicked()
{
	QFileDialog Qfd;
	openedFilePath = Qfd.getOpenFileName(this, tr("TextShredder File Selector"), QDir::currentPath(), QString("*.txt"));

	QString fileName = openedFilePath.mid(openedFilePath.lastIndexOf("/")+1, openedFilePath.length());

	if ( !openedFilePath.isEmpty() ) {
		addFileToFileTreeWidget( fileName );
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

void EditorView::addFileToFileTreeWidget( QString fileName )
{
	int rowCount = model.rowCount();

	FileManager::Instance()->addFileWithPath(fileName);
	QStandardItem *item = new QStandardItem( QString(fileName) );
	model.setItem(rowCount, 0, item);

	item->setCheckable( true );
	QStandardItem *status = new QStandardItem();

	model.setItem(rowCount, 1, status);

	ui->fileTreeWidget->setModel(&model);
}

void EditorView::addFolderToFileTreeWidget( QString directoryPath )
{
	QString directoryName = directoryPath.mid(directoryPath.lastIndexOf("/")+1, directoryPath.length());

	QDir dir;
	dir.setPath(directoryPath);
	QStringList filters("*.txt");
	QStringList list = dir.entryList(filters);

	int rowCount = model.rowCount();

	QStandardItem *item = new QStandardItem( QString(directoryName) );
	model.setItem(rowCount, 0, item);
	item->setCheckable( false );

	int i = 0;
	for(i = 0; i < list.count(); i++ ) {
		QString filePath = list.at(i);
		FileManager::Instance()->addFileWithPath(filePath);

		QStandardItem *child = new QStandardItem( filePath );
		child->setEditable( false );
		child->setCheckable( true );
		item->appendRow( child );
	}

	QStandardItem *status = new QStandardItem( QString("Not Syncing") );
	model.setItem(rowCount, 1, status);

	ui->fileTreeWidget->setModel(&model);
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
