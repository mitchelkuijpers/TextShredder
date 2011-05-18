#include "editorview.h"
#include "ui_editorview.h"
#include "syncablefiletextfield.h"
#include "../textshredder_core/libraries/synchronization/filemanager.h"

EditorView::EditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorView)
{
	ui->setupUi(this);
	ui->fileTreeWidget->setFocus();
	setFileTreeWidgetColumnsInModel();

	connect(FileManager::Instance(), SIGNAL(availableFilesChanged()), this, SLOT(rebuildSharedFilesListTreeView()));
}

EditorView::~EditorView()
{
    delete ui;
}

void EditorView::on_addFileButton_clicked()
{
	QFileDialog Qfd;
	QString openedFilePath = Qfd.getOpenFileName(this, tr("TextShredder File Selector"),
												 QDir::currentPath(), QString("*.txt"));

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
	model.setHorizontalHeaderItem(0, new QStandardItem(""));
	model.setHorizontalHeaderItem(1, new QStandardItem( "Files" ));
	model.setHorizontalHeaderItem(2, new QStandardItem( "Status" ));
}

void EditorView::addFileToFileTreeWidget( QString filePath )
{
	FileManager::Instance()->addFileWithPath(filePath);
	rebuildSharedFilesListTreeView();
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

	rebuildSharedFilesListTreeView();
}


void EditorView::rebuildSharedFilesListTreeView()
{
	QList < QSharedPointer<SyncableFile> > sharedFilesList =
			FileManager::Instance()->getAllFiles();

	int i = 0;
	for(i = 0; i < sharedFilesList.count(); i++ ) {
		QString fileName = sharedFilesList.at(i).data()->getFileAlias();

		QStandardItem *checkBox = new QStandardItem();
		if ( isServer ) {
			checkBox->setCheckable( true );
		}
		model.setItem(i, 0, checkBox);

		QStandardItem *item = new QStandardItem( fileName );
		item->setEditable( false );
		model.setItem(i, 1, item);

		QStandardItem *status = new QStandardItem( QString("Not Syncing") );
		model.setItem(i, 2, status);
	}

	ui->fileTreeWidget->setModel(&model);
}


void EditorView::on_fileTreeWidget_clicked(QModelIndex index)
{
	qDebug("A");
	if (index.column() == 0) {
		qDebug("B");
		QStandardItem *item = model.itemFromIndex(index);
		bool sharedState = (item->checkState() == Qt::Checked);
		QSharedPointer<SyncableFile>file =  FileManager::Instance()->getAllFiles().at(index.column());
		file.data()->setShared(sharedState);
	}
	//Check if row is checked. Set "isShared" = false
}

void EditorView::on_fileTreeWidget_doubleClicked(QModelIndex index)
{
	if (index.column() > 0) { //Should not be the checkBox column
		//You can't open a file twice! -> Not implemented yet
		const QAbstractItemModel * mod = index.model();
		QString fileName = mod->data(mod->index(index.row(), 0), Qt::DisplayRole).toString();
		openFileInEditor( fileName );
	}
}

void EditorView::openFileInEditor( QString fileName )
{
	QList < QSharedPointer<SyncableFile> > sharedFilesList =
			FileManager::Instance()->getAllFiles();

	SyncableFileTextField *textfield = new SyncableFileTextField(this);
	ui->openedFileTabs->addTab(textfield, fileName);


}

void EditorView::on_openedFileTabs_tabCloseRequested(int index)
{
	ui->openedFileTabs->removeTab(index);
}

void EditorView::setToServerMode()
{
	isServer = true;
	ui->addFileButton->setHidden(false);
	ui->addFolderButton->setHidden(false);
}

void EditorView::setToClientMode()
{
	isServer = false;
	ui->addFileButton->setHidden(true);
	ui->addFolderButton->setHidden(true);
}
