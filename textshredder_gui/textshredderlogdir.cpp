#include "textshredderlogdir.h"

#include <QDateTime>
#include <QtCore>

TextShredderLogDir * TextShredderLogDir::dirInstance = NULL;

TextShredderLogDir::TextShredderLogDir(QObject *parent) :
    QObject(parent)
{
    qDebug("Create dir");
    QDir dir;

    qDebug("Make dir");
    DirPath = "log ";
    DirPath.append(QDateTime::currentDateTime().toString("yyyymmddhhmmss"));
    dir.mkdir(DirPath);
    qDebug() << DirPath;
    qDebug() << dir.absolutePath ();
}

TextShredderLogDir * TextShredderLogDir::getInstance()
{
    if(!dirInstance){
        dirInstance = new TextShredderLogDir(NULL);
    }
    return dirInstance;
}

QString * TextShredderLogDir::getPath()
{
    return &DirPath;
}
