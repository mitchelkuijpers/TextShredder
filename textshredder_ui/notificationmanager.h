#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QWidget>
#include<QString>
#include<QPushButton>
#include<QGridLayout>
#include<QLabel>

#include "notificationoption.h"
#include "notification.h"

class NotificationManager : public QWidget
{
    Q_OBJECT
public:
	static NotificationManager * Instance( QObject *parent, Notification notification );
	void addButtonsToNotificationDialog( QList<NotificationOption*> notificationOption );
	void setWindowTitleBasedOnNotificationType();

private:
	Notification notification;
	QGridLayout *gridLayout;
	QLabel * messageLabel;
	enum NotificationType { SUCCESS, WARNING, ERROR, FATAL, INFO };
	static NotificationManager* sharedInstance;

signals:


public slots:

};

#endif // NOTIFICATIONMANAGER_H
