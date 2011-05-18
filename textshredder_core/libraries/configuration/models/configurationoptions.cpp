#include "configurationoptions.h"


ConfigurationOptions::ConfigurationOptions(QObject * parent):
	QObject(parent)
{
}

ConfigurationOptions::ConfigurationOptions(const ConfigurationOptions &copy):
		QObject(copy.parent())
{
	serverPort = copy.serverPort;
	lastKnownIpIndex = copy.lastKnownIpIndex;
	knownHostsList= copy.knownHostsList;
	lastKnownIp = copy.lastKnownIp;
}

ConfigurationOptions& ConfigurationOptions::operator =(const ConfigurationOptions& options)
{
	serverPort = options.serverPort;
	lastKnownIpIndex = options.lastKnownIpIndex;
	knownHostsList = options.knownHostsList;
	lastKnownIp = options.lastKnownIp;
	return *this;
}

void ConfigurationOptions::setServerPort(quint16 serverPortToSet)
{
	serverPort = serverPortToSet;
}


quint16 ConfigurationOptions::getServerPort()
{
	return serverPort;
}


void ConfigurationOptions::addHostToKnownHostsList(QString hostEntry)
{
	if(!knownHostsList.contains(hostEntry)) {
		knownHostsList.append(hostEntry);
	}
}

QStringList ConfigurationOptions::getKnownHostsList()
{
	return knownHostsList;
}

void ConfigurationOptions::setKnownHostsList(QStringList knownHosts)
{
	this->knownHostsList = knownHosts;
}


QString ConfigurationOptions::getLastKnownIp()
{
	return this->lastKnownIp;
}
void ConfigurationOptions::setLastKnownIp(QString lastKnownIpToSet)
{
	this->lastKnownIp = lastKnownIpToSet;
}

QDataStream &operator<<(QDataStream &out, ConfigurationOptions &options)
{
	out << options.getKnownHostsList() << QString::number(options.getServerPort()) << options.getLastKnownIp();
	return out;
}

QDataStream &operator>>(QDataStream &in, ConfigurationOptions &options)
{
	QString lastKnownIp;
	QStringList knownHosts;
	QString portString;

	in >> knownHosts >> portString >> lastKnownIp;

	options.setKnownHostsList(knownHosts);
	options.setServerPort(portString.toInt());
	options.setLastKnownIp(lastKnownIp);

	return in;
}
