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


QDataStream &operator<<(QDataStream &out, ConfigurationOptions &options)
{
	out << QString::number(options.getServerPort());
	out << options.getIp();
	return out;
}

QDataStream &operator>>(QDataStream &in, ConfigurationOptions &options)
{
	QString ip;
	QString portString;
	in >> portString >> ip;

	options.setServerPort(portString.toInt());
	options.setIp(ip);

	return in;
}
