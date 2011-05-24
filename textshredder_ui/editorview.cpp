#include "editorview.h"
#include "ui_editorview.h"

EditorView::EditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorView)
{
	ui->setupUi(this);
	ui->fileTreeWidget->setFocus();

	setFileTreeWidgetColumnsInModel();

	connect(FileManager::Instance(), SIGNAL(availableFilesChanged()), this, SLOT(rebuildSharedFilesListTreeView()));
	connect(PerformanceCalculator::Instance(), SIGNAL(newAverage(long)), this, SLOT(updateAveragePerformance(long)));
}

EditorView::~EditorView()
{
    delete ui;
}

void EditorView::on_addFileButton_clicked()
{
	QString openedFilePath = QFileDialog::getOpenFileName(this, tr("TextShredder File Selector"),
												 QDir::currentPath(),
												 QString("Text File (*.txt);;TextShredder Document (*.tsd);;HTML File (*.html)"));

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
	model.setHorizontalHeaderItem( 0, new QStandardItem( "Shared") );
	model.setHorizontalHeaderItem( 1, new QStandardItem( "Files" ) );
	model.setHorizontalHeaderItem( 2, new QStandardItem( "" ) );
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

void EditorView::on_fileTreeWidget_clicked(QModelIndex index)
{
	if (index.column() == 0 && isServer) {
		QStandardItem *item = model.itemFromIndex(index);
		bool sharedState = (item->checkState() == Qt::Checked);
		QSharedPointer<SyncableFile>file =  FileManager::Instance()->getAllFiles().at(index.row());
		file.data()->setShared(sharedState);
		rebuildSharedFilesListTreeView();
	}
}

void EditorView::rebuildSharedFilesListTreeView()
{
	QList < QSharedPointer<SyncableFile> > sharedFilesList =
			FileManager::Instance()->getAllFiles();
	qDebug() << "shardedFileList count: " << sharedFilesList.count();
	model.removeRows(0, model.rowCount());

	int i = 0;
	for(i = 0; i < sharedFilesList.count(); i++ ) {

		SyncableFile * syncableFile = sharedFilesList.at(i).data();

		addCheckBoxToSharedFilesListTreeView( i, syncableFile );
		addFileNameToSharedFilesListTreeView( i, syncableFile );
		addStatusIconToSharedFilesListTreeView( i, syncableFile );
	}

	ui->fileTreeWidget->setModel(&model);
	setColumnWidths();
}

void EditorView::addCheckBoxToSharedFilesListTreeView( int row, SyncableFile * syncableFile )
{
	QStandardItem *checkBox = new QStandardItem();
	if ( isServer ) {
		checkBox->setCheckable( true );
		if ( syncableFile->isShared() ) {
			checkBox->setCheckState(Qt::Checked);
		}
	}

	model.setItem(row, 0, checkBox);
}

void EditorView::addFileNameToSharedFilesListTreeView( int row, SyncableFile * syncableFile )
{
	QString fileName = syncableFile->getFileAlias();
	QStandardItem *file = new QStandardItem( fileName );
	file->setEditable( false );
	model.setItem(row, 1, file);
}

void EditorView::addStatusIconToSharedFilesListTreeView( int row, SyncableFile * syncableFile )
{
	QStandardItem *status = new QStandardItem( QString("") );

	switch( syncableFile->calculateStatus() ) {
		case 1:
			status->setIcon(QIcon(":/ui/status/images/status/user-offline.svg"));
			break;
		case 2:
			status->setIcon(QIcon(":/ui/status/images/status/user-offline.svg"));
			break;
		case 3:
			status->setIcon(QIcon(":/ui/status/images/status/user-editing.svg"));
			break;
		case 4:
			status->setIcon(QIcon(":/ui/status/images/status/user-editing.svg"));
			break;
		case 5:
			status->setIcon(QIcon(":/ui/status/images/status/user-idle.svg"));
			break;
		case 6:
			status->setIcon(QIcon(":/ui/status/images/status/user-available.svg"));
			break;
		case 7:
			status->setIcon(QIcon(":/ui/status/images/status/user-offline.svg"));
			break;
	}

	model.setItem(row, 2, status);
}

void EditorView::setColumnWidths()
{
	ui->fileTreeWidget->setColumnWidth(0, 44);
	ui->fileTreeWidget->setColumnWidth(1, 175);
	ui->fileTreeWidget->setColumnWidth(2, 30);
}

void EditorView::addFileToFileTreeWidget( QString filePath )
{
	FileManager::Instance()->addFileWithPath(filePath);
	rebuildSharedFilesListTreeView();
}

void EditorView::on_openedFileTabs_tabCloseRequested(int index)
{
	ui->openedFileTabs->removeTab(index);
	openedFilesList.at(index).data()->close();
	openedFilesList.removeAt(index);
}


void EditorView::on_fileTreeWidget_doubleClicked(QModelIndex index)
{
	if (index.column() > 0) {
		QSharedPointer<SyncableFile> file =  FileManager::Instance()->getAllFiles().at(index.row());

		if ( !file.data()->isOpened() )
			openFileInEditor( file );
	}
}

void EditorView::openFileInEditor( QSharedPointer<SyncableFile> file )
{
	QSharedPointer<SyncableFileTextField> textfield = QSharedPointer<SyncableFileTextField>(new SyncableFileTextField(this, file));
	ui->openedFileTabs->addTab(textfield.data(), file.data()->getFileAlias());

	openedFilesList.append(textfield);

	file.data()->open();

	if( !isServer ) {
		file.data()->requestSync();
	}
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

void EditorView::updateAveragePerformance(long averagePerformance)
{
}
