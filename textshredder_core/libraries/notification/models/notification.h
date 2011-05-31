#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include "notificationoption.h"

enum NotificationType {
	NotificationTypeSUCCESS,
	NotificationTypeWARNING,
	NotificationTypeERROR,
	NotificationTypeFATAL,
	NotificationTypeINFO
};

class Notification : public QObject
{
    Q_OBJECT
public:
	/**
	 * The constructor which needs a message and the the notification type
	 * @param parent Qobject pointer to access the methods
	 * @param message The message to be displayed
	 * @param notificationType The type of notification, needed for showing the correct type of notification
	 * @param hasCancelButton According to the type of notification, show the cancel button
	 */
	Notification( QObject *parent, QString message, int notificationType, bool hasCancelButton = true);
	/**
	 * The constructor which needs a message and the the notification type
	 * You can also pass a list of options which will be displayed.
	 * @param parent Qobject pointer to access the methods
	 * @param message The message to be displayed
	 * @param notificationType The type of notification, needed for showing the correct type of notification
	 * @param options A QList of notificationoptions.
	 * @param hasCancelButton According to the type of notification, show the cancel button
	 */
	Notification( QObject *parent, QString message, int notificationType, QList<NotificationOption>& options, bool hasCancelButton = true);

	/**
	 * Get the notification message
	 * @return The notification message
	 */
	QString getMessage();
	/**
	 * Get the notificationType
	 * @return The notification type
	 */
	int getNotificationType();
	/**
	 *Get the notification options
	 * @return A QList containing the notificationoptions
	 */
	QList<NotificationOption>& getNotificationOptions();
	/**
	 * Get if the notification has a cancelbutton
	 * @return TRUE/FALSE
	 */
	bool getHasCancelButton();
	/**
	 * Set the notification message
	 * @parm message The message to set
	 */
	void setMessage(QString message);
	/**
	 * Set the notificationType
	 * @param notificationType The notification type to set
	 */
	void setNotificationType(int notificationType);
	/**
	 * Set the notificationOptions
	 * @param options The notification options
	 */
	void setNotificationOptions(QList<NotificationOption>& options);
	/**
	 * Set if the option has a cancelbutton
	 * @param hasCancelButton True of False value
	 */
	void setHasCancelButton(bool hasCancelButton);

private:
	QString message;
	int notificationType;
	QList<NotificationOption>& options;
	bool hasCancelButton;

signals:

public slots:

};

#endif // NOTIFICATION_H
