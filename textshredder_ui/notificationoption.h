#ifndef NOTIFICATIONOPTION_H
#define NOTIFICATIONOPTION_H

#include <QObject>

class NotificationOption : public QObject
{
    Q_OBJECT
public:
	NotificationOption(const NotificationOption &other);
	NotificationOption(QObject *parent, const QString label);
	NotificationOption(QObject *parent, const QString label, void * function);
	QString getLabel();
	NotificationOption & operator =(const NotificationOption &);

private:
	QString label;
	void * function;

signals:

public slots:

};

#endif // NOTIFICATIONOPTION_H
