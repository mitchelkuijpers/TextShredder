#include "notificationmanager.h"

NotificationManager* NotificationManager::sharedInstance = NULL;

NotificationManager::NotificationManager( QObject *parent ) :
		QObject(parent)
{
}

NotificationManager * NotificationManager::Instance( )
{
	if ( !sharedInstance ) {
		sharedInstance = new NotificationManager(NULL);
	}
	return sharedInstance;
}


void NotificationManager::createNotificationDialog( Notification & notification )
{
	QDialog notificationDialog(NULL);
	notificationDialog.setFixedSize(350, 100);
	setWindowTitleBasedOnNotificationType( notification );

	gridLayout = new QGridLayout();
	messageLabel = new QLabel(notification.getMessage());
	gridLayout->addWidget(messageLabel, 0, 0);

	addButtonsToNotificationDialog(notification.getNotificationOptions());
	notificationDialog.setLayout(gridLayout);
}

void NotificationManager::addButtonsToNotificationDialog( QList<NotificationOption>& notificationOptions )
{
	int i;
	for(i = 0; i < notificationOptions.length(); i++ ) {
		//QPushButton * button = new QPushButton(notificationOptions.at(i).getLabel());
		//gridLayout->addWidget(button, 1, i);
	}
}

void NotificationManager::setWindowTitleBasedOnNotificationType( Notification & notification )
{
	QString windowTitle;

	switch( notification.getNotificationType() ) {
		case SUCCESS:
			windowTitle = "Succes";
			break;

		case WARNING:
			windowTitle = "Warning";
			break;

		case ERROR:
			windowTitle = "Error";
			break;

		case FATAL:
			windowTitle = "Fatal error";
			break;

		case INFO:
			windowTitle = "Information";
			break;

		default:
			windowTitle = "Unknown notification";
			break;
	}

	notificationDialog.setWindowTitle(windowTitle);
}
