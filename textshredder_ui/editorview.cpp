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
	QString openedFilePath = QFileDialog::getOpenFileName(this, tr("TextShredder File Selector"),
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
	model.setHorizontalHeaderItem(0, new QStandardItem("Shared"));
	model.setHorizontalHeaderItem(1, new QStandardItem( "Files" ));
	model.setHorizontalHeaderItem(2, new QStandardItem( "" ));

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


	model.removeRows(0, model.rowCount());
	int i = 0;
	for(i = 0; i < sharedFilesList.count(); i++ ) {

		SyncableFile * syncableFile = sharedFilesList.at(i).data();
		QString fileName = syncableFile->getFileAlias();

		//Checkbox
		QStandardItem *checkBox = new QStandardItem();
		if ( isServer ) {
			checkBox->setCheckable( true );
			if ( syncableFile->isShared() ) {
				checkBox->setCheckState(Qt::Checked);
			}
		}
		model.setItem(i, 0, checkBox);

		//Filename
		QStandardItem *file = new QStandardItem( fileName );
		file->setEditable( false );
		model.setItem(i, 1, file);

		//Status
		QStandardItem *status = new QStandardItem( QString("") );
		if ( syncableFile->isShared() ) {
			status->setIcon(QIcon(":/ui/status/images/status/user-available.svg"));
		} else {
			status->setIcon(QIcon(":/ui/status/images/status/user-offline.svg"));
		}
		model.setItem(i, 2, status);
	}

	ui->fileTreeWidget->setModel(&model);

	setColumnWidths();
}

void EditorView::setColumnWidths()
{
	ui->fileTreeWidget->setColumnWidth(0, 44);
	ui->fileTreeWidget->setColumnWidth(1, 175);
	ui->fileTreeWidget->setColumnWidth(2, 30);
}

void EditorView::on_fileTreeWidget_clicked(QModelIndex index)
{
	if (index.column() == 0) {
		QStandardItem *item = model.itemFromIndex(index);
		bool sharedState = (item->checkState() == Qt::Checked);
		QSharedPointer<SyncableFile>file =  FileManager::Instance()->getAllFiles().at(index.row());
		file.data()->setShared(sharedState);
		rebuildSharedFilesListTreeView();
	}
}

void EditorView::on_fileTreeWidget_doubleClicked(QModelIndex index)
{
	if (index.column() > 0) {
		qDebug() << "You can't open a file twice! -> Not implemented yet";
		openFileInEditor( index );
	}
}

void EditorView::openFileInEditor( QModelIndex index )
{
	QSharedPointer<SyncableFile> file =  FileManager::Instance()->getAllFiles().at(index.row());

	SyncableFileTextField *textfield = new SyncableFileTextField(this, file);
	ui->openedFileTabs->addTab(textfield, file.data()->getFileAlias());

	if( !isServer ) {
		file.data()->requestSync();
	}
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

	setWindowTitle("TextShredder Editor [SERVER]");
}

void EditorView::setToClientMode()
{
	isServer = false;
	ui->addFileButton->setHidden(true);
	ui->addFolderButton->setHidden(true);

	setWindowTitle("TextShredder Editor [CLIENT]");
}
