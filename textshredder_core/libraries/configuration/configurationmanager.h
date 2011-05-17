#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <QObject>
#include <QFile>
#include "models/configurationoptions.h"
#include "../network/textshredderconnection.h"
#include <QDataStream>

#define kDefaultConfigFile "/Users/maikdiepenbroek/MPNA/TextShredder/default_config.txt"

class ConfigurationManager
{

public:
	static ConfigurationManager * Instance();
	void load();
	void save();
	ConfigurationOptions getConfigurationOptions();
	void setConfigurationOptions(ConfigurationOptions newOptions);

private:
	ConfigurationManager();
	static ConfigurationManager* sharedInstance;
	QString fileName;
	ConfigurationOptions options;
signals:

public slots:

};




#endif // CONFIGURATIONMANAGER_H
