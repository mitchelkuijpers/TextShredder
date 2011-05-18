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
	QList<QString> getKnownHostsList();

	quint16 getServerPort();
	void setIp(QString ipToSet);
	void setServerPort(quint16 serverPortToSet);
	void addHostToKnownHostsList(QString hostEntry);

	ConfigurationOptions& operator =(const ConfigurationOptions&);

private:
	quint16 serverPort;
	QString ip;
	QList<QString> knownHostsList;
};

QDataStream &operator<<(QDataStream &out, ConfigurationOptions & options);
QDataStream &operator>>(QDataStream &in, ConfigurationOptions & options);

#endif // CONFIGURATIONOPTIONS_H
