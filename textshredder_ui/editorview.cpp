#include "editorview.h"
#include "ui_editorview.h"

EditorView::EditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorView)
{
    ui->setupUi(this);
}

EditorView::~EditorView()
{
    delete ui;
}
