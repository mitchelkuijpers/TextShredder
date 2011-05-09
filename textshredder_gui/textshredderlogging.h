#ifndef TEXTSHREDDERLOGGING_H
#define TEXTSHREDDERLOGGING_H

#include <QObject>
#include <QFile>

#define defaultLogFile "TextShredderLog"

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
    void writeLog(const char * logData);

signals:

public slots:

private:
    void setLogFile(const char * filePath);
    QFile * logFile;
};

#endif // TEXTSHREDDERLOGGING_H
