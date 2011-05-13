#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include "notificationoption.h"

class Notification : public QObject
{
    Q_OBJECT
public:
	explicit Notification( QString message, int notificationType, QList<NotificationOption*> options, QObject *parent = 0);
	QString getMessage();
	int getNotificationType();
	QList<NotificationOption*> getNotificationOptions();

private:
	QString message;
	int notificationType;
	enum NotificationType { SUCCESS, WARNING, ERROR, FATAL, INFO };
	QList<NotificationOption*> options;

signals:

public slots:

};

#endif // NOTIFICATION_H
