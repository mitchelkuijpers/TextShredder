#include "notification.h"

Notification::Notification( QString message, int notificationType, QList<NotificationOption*> options, QObject *parent = 0 ) :
		message(message), notificationType(notificationType), options(options), QObject(parent)
{
}

QString Notification::getMessage()
{
	return message;
}

int Notification::getNotificationType()
{
	return notificationType;
}

QList<NotificationOption*> Notification::getNotificationOptions()
{
	return options;
}
