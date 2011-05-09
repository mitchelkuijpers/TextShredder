#include "textshredderlogging.h"
#include <QTime>
#include <QTextStream>
#include <QDir>
#include <QtCore>


TextShredderLogging::TextShredderLogging(QObject *parent) :
    QObject(parent)
{
    setLogFile(defaultLogFile);
}

TextShredderLogging::TextShredderLogging(QObject *parent, QString fileName) :
        QObject(parent)
{
    setLogFile(fileName.toStdString().c_str());
}

void TextShredderLogging::setLogFile(const char *filePath)
{
	qDebug("Create dir");
    QDir dir;
    if(!dir.exists("log")){
		qDebug("Make dir");
        dir.mkdir("log");
    }
	qDebug() << dir.absolutePath ();
    QFile  * newLogFile;
    QString temp("log/");
    temp.append(filePath);

    temp.append(".txt");
	while (dir.exists (temp)) {
		temp.append ("+");
	}
    newLogFile = new QFile(temp);
    logFile = newLogFile;
    if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}


void TextShredderLogging::writeLog(const char * logData)
{
    QTextStream out(logFile);
	out << QTime::currentTime().toString() << " " << logData << "\n";
}
