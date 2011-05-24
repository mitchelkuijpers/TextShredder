#ifndef USERLISTVIEW_H
#define USERLISTVIEW_H

#include <QListWidget>

class UserListView : public QListWidget
{
    Q_OBJECT
public:
	explicit UserListView(QWidget *parent = 0);

signals:

private slots:
	void updateList();
};

#endif // USERLISTVIEW_H
