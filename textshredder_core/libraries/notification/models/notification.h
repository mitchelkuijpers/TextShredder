#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include "notificationoption.h"

class Notification : public QObject
{
    Q_OBJECT
public:
	Notification( QObject *parent, QString message, int notificationType, bool hasCancelButton = true);
	Notification( QObject *parent, QString message, int notificationType, QList<NotificationOption>& options, bool hasCancelButton = true);

	QString getMessage();
	int getNotificationType();
	QList<NotificationOption>& getNotificationOptions();
	bool getHasCancelButton();

	void setMessage(QString message);
	void setNotificationType(int notificationType);
	void setNotificationOptions(QList<NotificationOption>& options);
	void setHasCancelButton(bool hasCancelButton);

private:
	QString message;
	int notificationType;
	enum NotificationType { SUCCESS, WARNING, ERROR, FATAL, INFO };
	QList<NotificationOption>& options;
	bool hasCancelButton;

signals:

public slots:

};

#endif // NOTIFICATION_H
