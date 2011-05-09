#include "editorribbon.h"
#include "ui_editorribbon.h"

EditorRibbon::EditorRibbon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorRibbon)
{
    ui->setupUi(this);
}

EditorRibbon::~EditorRibbon()
{
    delete ui;
}
