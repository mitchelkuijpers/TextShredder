#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QWidget>

namespace Ui {
	class SyncableFileTextField;
}

class SyncableFileTextField : public QWidget
{
    Q_OBJECT

public:
	explicit SyncableFileTextField(QWidget *parent = 0);
	~SyncableFileTextField();

private:
	Ui::SyncableFileTextField *ui;
};

#endif // TEXTFIELD_H
