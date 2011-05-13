#ifndef NOTIFICATIONOPTION_H
#define NOTIFICATIONOPTION_H

#include <QObject>

class NotificationOption : public QObject
{
    Q_OBJECT
public:
	NotificationOption(QString label);
	NotificationOption(QString label, void * function);
	QString getLabel();

private:
	QString label;
	void * function;

signals:

public slots:

};

#endif // NOTIFICATIONOPTION_H
