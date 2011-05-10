#include "debugview.h"
#include "ui_debugview.h"

DebugView::DebugView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugView)
{
    ui->setupUi(this);
}

DebugView::~DebugView()
{
    delete ui;
}
