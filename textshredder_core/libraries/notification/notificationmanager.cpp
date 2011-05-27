#include "notificationmanager.h"
#include <QDebug>

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
	notificationDialog = new QDialog(NULL);
	notificationDialog->setMinimumSize(400, 100);
	notificationDialog->setMaximumSize(600, 200);
	setWindowTitleBasedOnNotificationType( notification );

	gridLayout = new QGridLayout();
	notificationDialog->setLayout(gridLayout);

	addButtonsToNotificationDialog( notification );

	messageLabel = new QLabel(notification.getMessage());
	gridLayout->addWidget(messageLabel, 0, 0, 2, totalAmountOfButtons);

	notificationDialog->exec();
	notificationDialog->deleteLater();
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

	notificationDialog->setWindowTitle(windowTitle);
}

void NotificationManager::addButtonsToNotificationDialog( Notification & notification  )
{
	if ( notification.getHasCancelButton() ) {
		QPushButton * button = new QPushButton("Ok");
		gridLayout->addWidget(button, 1, 0);
		connect(button, SIGNAL(clicked()), notificationDialog, SLOT(close()));
	}

	totalAmountOfButtons = 1;
}
