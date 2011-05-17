#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QWidget>

namespace Ui {
    class TextField;
}

class TextField : public QWidget
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

private:
    Ui::TextField *ui;
};

#endif // TEXTFIELD_H
