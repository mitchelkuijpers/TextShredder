#include "usermanager.h"
#include <QDebug>
UserManager * UserManager::sharedInstance = NULL;


UserManager * UserManager::Instance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new UserManager(NULL);
	}
	return sharedInstance;
}



UserManager::UserManager(QObject *parent) :
    QObject(parent)
{
}

void UserManager::addAlias(QString alias)
{
	qDebug() << "UserManager::addAlias(QString alias)" << alias;
	userNames.append(alias);
	emit usersChanged();
}

void UserManager::removeAlias(QString alias)
{
	qDebug() << "UserManager::removeAlias(QString alias)" << alias;
	int index = userNames.indexOf(alias);
	userNames.removeAt(index);
	emit usersChanged();
}

void UserManager::clearAndAddList(QList<QString> newList) {
	userNames.clear();
	qDebug() << "Usernames count "<< userNames.count();
	userNames.append(newList);
	qDebug() << "Usernames count "<< userNames.count();
	emit usersChanged();
}

QList<QString> UserManager::getUsers()
{
	return userNames;
}


