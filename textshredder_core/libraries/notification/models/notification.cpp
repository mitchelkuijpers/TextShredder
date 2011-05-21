#include "notification.h"

Notification::Notification( QObject *parent, QString message, int notificationType,
							bool hasCancelButton ) :
		QObject(parent), message(message), notificationType(notificationType),
		options(options), hasCancelButton(hasCancelButton)
{
}

Notification::Notification( QObject *parent, QString message, int notificationType,
							QList<NotificationOption>& options, bool hasCancelButton ) :
		QObject(parent), message(message), notificationType(notificationType),
		options(options), hasCancelButton(hasCancelButton)
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

bool Notification::getHasCancelButton()
{
	return hasCancelButton;
}

void Notification::setMessage( QString message )
{
	this->message = message;
}

void Notification::setNotificationType( int notificationType )
{
	this->notificationType = notificationType;
}

void Notification::setNotificationOptions( QList<NotificationOption>& options )
{
	this->options = options;
}

void Notification::setHasCancelButton( bool hasCancelButton )
{
	this->hasCancelButton = hasCancelButton;
}
