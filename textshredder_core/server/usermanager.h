#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

class UserManager : public QObject
{
    Q_OBJECT
public:
	static UserManager *Instance();

	void addAlias(QString alias);
	void removeAlias(QString alias);
	void clearAndAddList(QList<QString> newList);
	QList<QString> getUsers();

private:
	static UserManager *sharedInstance;
	UserManager(QObject *parent = 0);
	QList<QString> userNames;

signals:
	void usersChanged();
public slots:

};

#endif // USERMANAGER_H
