#include "userlistview.h"
#include "../textshredder_core/server/usermanager.h"
#include <QDebug>

UserListView::UserListView(QWidget *parent) :
	QListWidget(parent)
{
	connect(UserManager::Instance(), SIGNAL(usersChanged()),
			this, SLOT(updateList()));
}


void UserListView::updateList()
{
	qDebug("UserListView::updateList");
	while (count() > 0) {
		QListWidgetItem *rowItem = takeItem(0);
		delete rowItem;
	}

	QList<QString> users = UserManager::Instance()->getUsers();
	for (int i = 0; i < users.count(); i++ ) {
		QListWidgetItem *rowItem = new QListWidgetItem(users.at(i));
		addItem(rowItem);
		qDebug() << "Got here '" <<  users.at(i) << '\'';
	}
	qDebug() << "Users in list should be :" << users.count();
}

