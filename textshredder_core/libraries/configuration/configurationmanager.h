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
	/**
	  * Returns a singleton Configuration manager *
	  */
	static ConfigurationManager * Instance();
	/**
	  * Loads the configurationoptions from a file.
	  * Writes the options to the options variable
	  */
	void load();
	/**
	  * Saves the configurationoptions to a file.
	  * Writes to the file from the options variable
	  */
	void save();
	/**
	  * Returns the configuration options
	  */
	ConfigurationOptions getConfigurationOptions();
	/**
	  * Sets the new configurationOptions
	  * @param newOptions the options to set
	  */
	void setConfigurationOptions(ConfigurationOptions newOptions);

private:
	/**
	  * Constructor which sets the filename and the options
	  */
	ConfigurationManager();
	/**
	  * Returns a singleton ConfigurationManager*
	  */
	static ConfigurationManager* sharedInstance;
	QString fileName;

	ConfigurationOptions options;
};




#endif // CONFIGURATIONMANAGER_H
