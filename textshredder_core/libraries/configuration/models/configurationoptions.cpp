#include "configurationoptions.h"


ConfigurationOptions::ConfigurationOptions(QObject * parent):
	QObject(parent)
{
}

ConfigurationOptions::ConfigurationOptions(const ConfigurationOptions &copy):
		QObject(copy.parent())
{
	serverPort = copy.serverPort;
	ip = copy.ip;
	knownHostsList= copy.knownHostsList;
}

ConfigurationOptions& ConfigurationOptions::operator =(const ConfigurationOptions& options)
{
	serverPort = options.serverPort;
	ip = options.ip;

	return *this;
}

void ConfigurationOptions::setServerPort(quint16 serverPortToSet)
{
	serverPort = serverPortToSet;
}

void ConfigurationOptions::setIp(QString ipToSet)
{
	ip = ipToSet;
}

quint16 ConfigurationOptions::getServerPort()
{
	return serverPort;
}

QString ConfigurationOptions::getIp()
{
	return ip;
}

void ConfigurationOptions::addHostToKnownHostsList(QString hostEntry)
{
	knownHostsList.append(hostEntry);
}

QList<QString> ConfigurationOptions::getKnownHostsList()
{
	return knownHostsList;
}


QDataStream &operator<<(QDataStream &out, ConfigurationOptions &options)
{
	out << options.getIp();
	out << QString::number(options.getServerPort());
	return out;
}

QDataStream &operator>>(QDataStream &in, ConfigurationOptions &options)
{
	QString ip;
	QString portString;
	in >> ip >> portString;

	options.setIp(ip);
	options.setServerPort(portString.toInt());

	return in;
}
