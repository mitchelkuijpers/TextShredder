#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDialog>

#include "notificationoption.h"
#include "notification.h"

class NotificationManager : public QObject
{
    Q_OBJECT
public:
	static NotificationManager * Instance();
	void addButtonsToNotificationDialog( QList<NotificationOption*> notificationOptions );
	void newNotificationDialog( Notification * notification);
	void createNotificationDialog( Notification * notification);
	void setNotification( Notification * notification );
	void setWindowTitleBasedOnNotificationType( Notification * notification );

private:
	NotificationManager(QObject *parent = 0);
	QDialog notificationDialog;
	QGridLayout *gridLayout;
	QLabel * messageLabel;
	enum NotificationType { SUCCESS, WARNING, ERROR, FATAL, INFO };
	static NotificationManager* sharedInstance;

signals:


public slots:

};

#endif // NOTIFICATIONMANAGER_H
