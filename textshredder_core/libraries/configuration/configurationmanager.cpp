#include "configurationmanager.h"

ConfigurationManager * ConfigurationManager::sharedInstance = NULL;

ConfigurationManager::ConfigurationManager() :
		fileName(kDefaultConfigFile), options(NULL)
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
	if ( file.open( QIODevice::WriteOnly) )
	{
		QDataStream out(&file);
		out << options;
	}
	else {
		qDebug("Couldn't open file");
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
