#include "textshredderlogging.h"
#include <QTime>
#include <QTextStream>
#include <QDir>


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
    QDir dir;
    if(!dir.exists("log")){
        dir.mkdir("log");
    }
    QFile  * newLogFile;
    QString temp("log/");
    temp.append(filePath);

    temp.append(".txt");
    newLogFile = new QFile(temp);
    logFile = newLogFile;
    if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}


void TextShredderLogging::writeLog(const char * logData)
{
    QTextStream out(logFile);
    out << QTime::currentTime().toString() << " " << logData ;
}
