#ifndef CONFIGURATIONMANAGERTESTS_H
#define CONFIGURATIONMANAGERTESTS_H
#include "../textshredder_core/libraries/configuration/configurationmanager.h"
#include "../textshredder_core/libraries/configuration/models/configurationoptions.h"
#include <QObject>
#include <QtCore/QString>
#include "autotest.h"

class ConfigurationManagerTests: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void testSetNewOptions();
};
DECLARE_TEST(ConfigurationManagerTests);

#endif // CONFIGURATIONMANAGERTESTS_H
