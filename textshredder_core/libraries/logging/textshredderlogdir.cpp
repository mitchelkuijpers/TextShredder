#include "textshredderlogdir.h"

#include <QDateTime>
#include <QtCore>

TextShredderLogDir * TextShredderLogDir::dirInstance = NULL;

TextShredderLogDir::TextShredderLogDir(QObject *parent) :
    QObject(parent)
{
	QDir dir;
	DirPath = "log_";
	DirPath.append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

	dir.mkdir(DirPath);
}

TextShredderLogDir * TextShredderLogDir::getInstance()
{
	if( !dirInstance ) {
		dirInstance = new TextShredderLogDir(NULL);
	}
	return dirInstance;
}

QString * TextShredderLogDir::getPath()
{
	return &DirPath;
}
