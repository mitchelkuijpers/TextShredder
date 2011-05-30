#ifndef NOTIFICATIONOPTION_H
#define NOTIFICATIONOPTION_H

#include <QObject>

class NotificationOption : public QObject
{
    Q_OBJECT
public:
	/**
	 * The copy constructor
	 * @param other A constant NotificationOption object
	 */
	NotificationOption(const NotificationOption &other);
	/**
	 * The constructor
	 * @param parent Qobject pointer to access the methods
	 * @param label The label variable is set.
	 */
	NotificationOption(QObject *parent, const QString label);
	/**
	 * The constructor
	 * @param parent Qobject pointer to access the methods
	 * @param label The label variable is set.
	 * @param function A void pointer to a passed function.
	 */
	NotificationOption(QObject *parent, const QString label, void * function);
	/**
	 * Get the notification label
	 */
	QString getLabel();
	/**
	 * The equals operator is overloaded to set the notificationOption
	 * @param NotificationOption& The Notification option to set
	 */
	NotificationOption & operator =(const NotificationOption &);

private:
	QString label;
	void * function;

signals:


public slots:

};

#endif // NOTIFICATIONOPTION_H
