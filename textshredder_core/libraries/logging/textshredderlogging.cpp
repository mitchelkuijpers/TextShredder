#include "textshredderlogging.h"
#include "textshredderlogdir.h"
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

    QFile  * newLogFile;
    QString temp(TextShredderLogDir::getInstance()->getPath()->toStdString().c_str());
    temp.append("/");
    temp.append(filePath);

    temp.append(".txt");
    newLogFile = new QFile(temp);
    logFile = newLogFile;
    if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}

void TextShredderLogging::writeLog(QString &logData)
{
    QTextStream out(logFile);
    out << QTime::currentTime().toString() << " " << logData << "\n";
}

void TextShredderLogging::writeLog(QString &logData, LogType logtype)
{
    QTextStream out(logFile);
    switch(logtype){
    case INFO:
        logData.prepend("INFO -> ");
        break;
    case DEBUG:
        logData.prepend("DEBUG -> ");
        break;
    case ERROR:
        logData.prepend("ERROR -> ");
        break;
    }
    writeLog(logData);

}
