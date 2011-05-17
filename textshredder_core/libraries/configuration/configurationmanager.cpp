#include "configurationmanager.h"

ConfigurationManager * ConfigurationManager::sharedInstance = NULL;

ConfigurationManager::ConfigurationManager() :
		options(NULL), fileName(kDefaultConfigFile)
{
}

void ConfigurationManager::load()
{
	QFile file(fileName);
	if(file.exists(fileName)) {
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		in >> options;
	}
}


void ConfigurationManager::save()
{
	QFile file(fileName);
	if(file.exists(fileName)) {
		file.open(QIODevice::WriteOnly);
		QDataStream out(&file);
		out << options;
	}
}

ConfigurationManager * ConfigurationManager::Instance()
{
	if ( !sharedInstance ) {
		sharedInstance = new ConfigurationManager();
	}
	return sharedInstance;
}

ConfigurationOptions ConfigurationManager::getConfigurationOptions()
{
	return options;
}

void ConfigurationManager::setConfigurationOptions(ConfigurationOptions newOptions)
{
	options = newOptions;
}
