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
	void addButtonsToNotificationDialog( QDialog * notificationDialog, QList<NotificationOption>& notificationOptions );
	void createNotificationDialog( Notification & notification);
	void setWindowTitleBasedOnNotificationType( QDialog * notificationDialog, Notification & notification );

private:
	NotificationManager(QObject *parent = 0);
	QGridLayout *gridLayout;
	QLabel * messageLabel;
	enum NotificationType { SUCCESS, WARNING, ERROR, FATAL, INFO };
	static NotificationManager* sharedInstance;
	int totalAmountOfButtons;

signals:


public slots:

private slots:
	void closeDialog();
};

#endif // NOTIFICATIONMANAGER_H