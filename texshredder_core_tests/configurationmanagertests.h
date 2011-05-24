#ifndef CONFIGURATIONMANAGERTESTS_H
#define CONFIGURATIONMANAGERTESTS_H
#include "../textshredder_core/libraries/configuration/configurationmanager.h"
#include <QObject>
#include <QtCore>
#include "autotest.h"
class ConfigurationManagerTests: public QObject
{
	Q_OBJECT

public:
	void testSetNewOptions();

};
QBool operator !=(ConfigurationOptions, QBool);

DECLARE_TEST(ConfigurationManagerTests);

#endif // CONFIGURATIONMANAGERTESTS_H
