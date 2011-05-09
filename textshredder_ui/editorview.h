#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QMainWindow>

namespace Ui {
    class EditorView;
}

class EditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorView(QWidget *parent = 0);
    ~EditorView();

private:
    Ui::EditorView *ui;
};

#endif // EDITORVIEW_H
