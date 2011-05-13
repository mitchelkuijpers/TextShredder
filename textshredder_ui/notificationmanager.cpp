#include "notificationmanager.h"

NotificationManager* NotificationManager::sharedInstance = NULL;

NotificationManager::NotificationManager(QObject *parent) :
		QObject(parent)
{
}

NotificationManager * NotificationManager::Instance( Notification notification ) :
	notification(notification)
{

	this->setFixedSize(350, 100);
	setWindowTitleBasedOnNotificationType();

	gridLayout = new QGridLayout(this);

	messageLabel = new QLabel(notification.getMessage());
	gridLayout->addWidget(messageLabel, 0, 0);


	addButtonsToNotificationDialog(notification.getNotificationOptions());

	setLayout(gridLayout);
}

void NotificationManager::addButtonsToNotificationDialog( QList<NotificationOption*> notificationOptions )
{
	int i;
	for(i = 0; i < notificationOptions.length(); i++ ) {
		QPushButton * button = new QPushButton(notificationOptions.at(i)->getLabel(), this);
		gridLayout->addWidget(button, 1, i);
	}
}

void NotificationManager::setWindowTitleBasedOnNotificationType()
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

	this->setWindowTitle(windowTitle);
}
