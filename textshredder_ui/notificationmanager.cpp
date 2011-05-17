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
	QDialog notificationDialog(NULL);
	notificationDialog.setFixedSize(400, 100);
	setWindowTitleBasedOnNotificationType( &notificationDialog, notification );

	gridLayout = new QGridLayout();
	notificationDialog.setLayout(gridLayout);

	totalAmountOfButtons = notification.getNotificationOptions().length();
	messageLabel = new QLabel(notification.getMessage());
	gridLayout->addWidget(messageLabel, 0, 0, 2, totalAmountOfButtons);

	addButtonsToNotificationDialog( &notificationDialog, notification.getNotificationOptions());

	notificationDialog.exec();
	notificationDialog.show();
}

void NotificationManager::setWindowTitleBasedOnNotificationType( QDialog * notificationDialog, Notification & notification )
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

void NotificationManager::addButtonsToNotificationDialog( QDialog * notificationDialog, QList<NotificationOption>& notificationOptions )
{
	int i;
	for(i = 0; i < notificationOptions.length(); i++ ) {
		NotificationOption option = notificationOptions.at(i);
		QPushButton * button = new QPushButton(option.getLabel());
		gridLayout->addWidget(button, 3, i);
		connect(button, SIGNAL(clicked()), this, SLOT(closeDialog()));
	}
}

void NotificationManager::closeDialog()
{
	qDebug("Close Dialog");
}
