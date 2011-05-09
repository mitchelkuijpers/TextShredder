#ifndef EDITORRIBBON_H
#define EDITORRIBBON_H

#include <QWidget>

namespace Ui {
    class EditorRibbon;
}

class EditorRibbon : public QWidget
{
    Q_OBJECT

public:
    explicit EditorRibbon(QWidget *parent = 0);
    ~EditorRibbon();

private:
    Ui::EditorRibbon *ui;
};

#endif // EDITORRIBBON_H
