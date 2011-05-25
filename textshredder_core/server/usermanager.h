#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

class UserManager : public QObject
{
    Q_OBJECT
public:
	/**
	 * Returns a singleton instance of the UserManager
	 */
	static UserManager *Instance();
	/**
	 * Adds the given alias to the list of usernames
	 * @param alias The alias to add
	 */
	void addAlias(QString alias);
	/**
	 * Removes the alias from the list of usernames
	 * @param alias The alias to remove from the list of usernames
	 */
	void removeAlias(QString alias);
	/**
	 * Clears the username list and adds the new names in the given list
	 * @param newList The list which contains the new names.
	 */
	void clearAndAddList(QList<QString> newList);
	/**
	 * Get all the users from the list
	 * @return userNames
	 */
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
