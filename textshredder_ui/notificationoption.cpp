#include "notificationoption.h"

NotificationOption::NotificationOption(QString label) :
	label(label)
{
}

NotificationOption::NotificationOption(QString label, void * function) :
	label(label), function(function)
{
}

QString NotificationOption::getLabel()
{
	return label;
}
