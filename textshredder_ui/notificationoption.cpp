#include "notificationoption.h"

NotificationOption::NotificationOption(QObject *parent, const QString label) :
		QObject(parent)
{
	this->label = label;
}

NotificationOption::NotificationOption(QObject *parent, const QString label, void * function) :
		QObject(parent)
{
	this->label = label;
	this->function = function;
}

NotificationOption::NotificationOption(const NotificationOption &other) : QObject(other.parent())
{
	this->label = other.label;
	this->function = other.function;
}

NotificationOption & NotificationOption::operator =(const NotificationOption & other)
{
	this->label = other.label;
	this->function = other.function;
}

QString NotificationOption::getLabel()
{
	return label;
}
