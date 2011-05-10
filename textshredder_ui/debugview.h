#ifndef DEBUGVIEW_H
#define DEBUGVIEW_H

#include <QDialog>

namespace Ui {
    class DebugView;
}

class DebugView : public QDialog
{
    Q_OBJECT

public:
    explicit DebugView(QWidget *parent = 0);
    ~DebugView();

private:
    Ui::DebugView *ui;
};

#endif // DEBUGVIEW_H
