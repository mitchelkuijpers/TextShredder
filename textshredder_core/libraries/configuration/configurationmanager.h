#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QObject>
#include <QFile>
#include "models/configurationoptions.h"
#include "../network/textshredderconnection.h"
#include <QDataStream>

#define kDefaultConfigFile "default_config.txt"

class ConfigurationManager
{

public:
	static ConfigurationManager * Instance();
	void load();
	void save();
	ConfigurationOptions getConfigurationOptions();
	void setConfigurationOptions();

private:
	ConfigurationManager();
	ConfigurationOptions options;
	static ConfigurationManager* sharedInstance;
	QString fileName;

signals:

public slots:

};




#endif // CONFIGURATIONMANAGER_H
