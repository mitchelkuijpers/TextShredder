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
	ConfigurationOptions(QObject *);
	ConfigurationOptions(const ConfigurationOptions &);
	QString getIp();
	QStringList getKnownHostsList();
	quint16 getLastKnownIpIndex();
	QString getLastKnownIp();

	quint16 getServerPort();
	void setIp(QString ipToSet);
	void setServerPort(quint16 serverPortToSet);
	void addHostToKnownHostsList(QString hostEntry);
	void setKnownHostsList(QStringList knownHosts);
	void setLastKnownIpIndex(quint16 lastKnownIpIndexToBeInserted);
	void setLastKnownIp(QString lastKnownIpToSet);
	QString getLastUsedAlias();
	void setLastUsedAlias(QString lastUsedAliasToSet);
	ConfigurationOptions& operator =(const ConfigurationOptions&);

private:
	quint16 serverPort;
	QString lastKnownIp;
	QStringList knownHostsList;
	quint16 lastKnownIpIndex;
	QString lastUsedAlias;
};

QDataStream &operator<<(QDataStream &out, ConfigurationOptions & options);
QDataStream &operator>>(QDataStream &in, ConfigurationOptions & options);

#endif // CONFIGURATIONOPTIONS_H
