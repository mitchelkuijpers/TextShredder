#ifndef CONFIGURATIONOPTIONS_H
#define CONFIGURATIONOPTIONS_H

#include <QObject>
#include <QString>
#include <QDataStream>
#include "../../network/textshredderconnection.h"

class ConfigurationOptions : public QObject
{
	Q_OBJECT

public:
	/**
	 * Constructor.  Initializes the ConfigurationOptions with the QObject methods available.
	 * @param Qobject*
	 */
	ConfigurationOptions(QObject *);
	/**
	 * Copy Constructor. creates a copy of all the private variables
	 * @param Qobject*
	 */
	ConfigurationOptions(const ConfigurationOptions &);
	/**
	 * Gets the knownhostList
	 * @return a qlist Which holds the known hosts
	 */
	QStringList getKnownHostsList();
	/**
	 * Gets the lastknownipindex
	 * @return quint16 Which holds the lastknownipindex
	 */
	quint16 getLastKnownIpIndex();
	/**
	 * Gets the lastKnown ip
	 * @return The last known ip
	 */
	QString getLastKnownIp();
	/**
	 * Gets the server port which was last used
	 * @return The serverport
	 */
	quint16 getServerPort();
	/**
	 * Sets the serverport variable to the parameter
	 * @param serverPortToSet The serverport to set
	 */
	void setServerPort(quint16 serverPortToSet);
	/**
	 * Adds the host to the knownhostlist
	 * @param hostEntry the ip to add to the knownhosts
	 */
	void addHostToKnownHostsList(QString hostEntry);
	/**
	 * Sets the knownHosts list to the list given as the parameter
	 * @param knownHosts List which holds the knownhosts
	 */
	void setKnownHostsList(QStringList knownHosts);
	/**
	 * Sets last known ip
	 * @param lastKnownIpToSet The ip to set as last known
	 */
	void setLastKnownIp(QString lastKnownIpToSet);
	/**
	 * Gets the lastUsedAlias
	 * @return the last used alias
	 */
	QString getLastUsedAlias();
	/**
	 * Sets last known used alias
	 * @param lastUsedAliasToSet The alias to set as last known
	 */
	void setLastUsedAlias(QString lastUsedAliasToSet);
	/**
	 * The equals operator is overloaded to handle the configuration options
	 * @param ConfigurationOptions&
	 */
	ConfigurationOptions& operator =(const ConfigurationOptions&);

private:
	quint16 serverPort;
	QString lastKnownIp;
	QStringList knownHostsList;
	quint16 lastKnownIpIndex;
	QString lastUsedAlias;
};
/**
 * The << operator is overloaded to handle the configuration options
 * @param &out where to write to
 * @param options the configurationOptions
 */
QDataStream &operator<<(QDataStream &out, ConfigurationOptions & options);
/**
 * The >> operator is overloaded to handle the configuration options
 * @param &in Where to write from
 * @param options The configurationOptions
 */
QDataStream &operator>>(QDataStream &in, ConfigurationOptions & options);

#endif // CONFIGURATIONOPTIONS_H
