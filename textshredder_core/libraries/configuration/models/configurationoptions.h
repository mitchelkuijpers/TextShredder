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
	quint16 getServerPort();
	void setIp(QString ipToSet);
	void setServerPort(quint16 serverPortToSet);

	ConfigurationOptions& operator =(const ConfigurationOptions&);

private:
	quint16 serverPort;
	QString ip;
};

QDataStream &operator<<(QDataStream &out, ConfigurationOptions & options);
QDataStream &operator>>(QDataStream &in, ConfigurationOptions & options);

#endif // CONFIGURATIONOPTIONS_H
