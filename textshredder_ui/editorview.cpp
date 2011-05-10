#include "editorview.h"
#include "ui_editorview.h"
#include <QtCore/QDebug>

EditorView::EditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorView)
{
    ui->setupUi(this);

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
	ui->fileNameLabel->setText(fileName);

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

	QStandardItem *item = new QStandardItem( QString(fileName) );
	model.setItem(rowCount, 0, item);

	QStandardItem *status = new QStandardItem( QString("Not Syncing") );
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

	int i = 0;
	for(i = 0; i < list.count(); i++ ) {
		QStandardItem *child = new QStandardItem( QString(list.at(i)) );
		child->setEditable( false );
		item->appendRow( child );
	}

	QStandardItem *status = new QStandardItem( QString("Not Syncing") );
	model.setItem(rowCount, 1, status);

	ui->fileTreeWidget->setModel(&model);
}

void EditorView::on_fileTreeWidget_clicked(QModelIndex index)
{

	const QAbstractItemModel * mod = index.model();
	QString fName = mod->data(mod->index(index.row(), index.column()), Qt::DisplayRole).toString();

	ui->fileNameLabel->setText( fName );
}
