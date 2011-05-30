#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDialog>

#include "models/notificationoption.h"
#include "models/notification.h"

class NotificationManager : public QObject
{
    Q_OBJECT
public:
	/**
	 * Returns a singleton instance of the NotificationManager
	 */
	static NotificationManager * Instance();
	/**
	 *	Adds the correct buttons to the notification dialog
	 * @param notification The notification to get the correct buttons from
	 */
	void addButtonsToNotificationDialog( Notification & notification  );
	/**
	 * Creates the noticifation dialog
	 * @param notification The notification which represents the dialog
	 */
	void createNotificationDialog( Notification & notification);
	/**
	 * Sets the title of the window to the correct notification type
	 * @param notification The notification on which the title is based
	 */
	void setWindowTitleBasedOnNotificationType( Notification & notification );
	QDialog * notificationDialog;

private:
	NotificationManager(QObject *parent = 0);
	QGridLayout *gridLayout;
	QLabel * messageLabel;
	enum NotificationType { SUCCESS, WARNING, ERROR, FATAL, INFO };
	static NotificationManager* sharedInstance;

signals:


public slots:

private slots:

};

#endif // NOTIFICATIONMANAGER_H
