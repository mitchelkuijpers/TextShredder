#include "configurationmanagertests.h"

void ConfigurationManagerTests::testSetNewOptions()
{
	ConfigurationManager::Instance()->load();
	ConfigurationOptions configOptions = ConfigurationManager::Instance()->getConfigurationOptions();
	quint16 oldServerPort = configOptions.getServerPort();
	QString oldServerIp = configOptions.getLastKnownIp();
	QString oldAlias = configOptions.getLastUsedAlias();

	QString newIp = "2939.33.3.3";
	configOptions.setServerPort((quint16) 3939);
	configOptions.setLastKnownIp(newIp);
	configOptions.setLastUsedAlias(QString("Berend Botje"));
	ConfigurationManager::Instance()->save();

	QVERIFY2(oldServerPort != configOptions.getServerPort(), "The serverport has not changed");
	QVERIFY2(oldServerIp != configOptions.getLastKnownIp(), "The ip has not changed");
	QVERIFY2(oldAlias != configOptions.getLastUsedAlias(), "The alias has not changed");
}
