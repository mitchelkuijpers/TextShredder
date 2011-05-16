#include "notification.h"

Notification::Notification( QObject *parent, QString message, int notificationType, QList<NotificationOption>& options ) :
		QObject(parent), message(message), notificationType(notificationType), options(options)
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

QList<NotificationOption>& Notification::getNotificationOptions()
{
	return options;
}
