#ifndef TEXTSHREDDERLOGGING_H
#define TEXTSHREDDERLOGGING_H

#include <QObject>
#include <QFile>
#include <QStringList>

#define defaultLogFile "TextShredderLog"

typedef enum{
    INFO,
    DEBUG,
    ERROR
} LogType;

class TextShredderLogging : public QObject
{
    Q_OBJECT
public:
    /**
      * Create TextShredderLogging with default Log File to write too
      */
    TextShredderLogging(QObject *parent);

    /**
      * Create TextShredderLogging with specific file
      */
    TextShredderLogging(QObject *parent, QString fileName);

    /**
      * Write data to the log, with current time
      */
    void writeLog(QString &logData);
    void writeLog(QString &logData, LogType logtype);



signals:

public slots:

private:
    void setLogFile(const char * filePath);
    QFile * logFile;

};

#endif // TEXTSHREDDERLOGGING_H
