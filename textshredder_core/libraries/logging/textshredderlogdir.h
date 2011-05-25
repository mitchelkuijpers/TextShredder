#ifndef TEXTSHREDDERLOGDIR_H
#define TEXTSHREDDERLOGDIR_H

#include <QObject>
#include <QDir>

class TextShredderLogDir : public QObject
{
    Q_OBJECT
public:
	/**
	  * Returns a TextShredderLogDir singleton instance
	  */
    static TextShredderLogDir * getInstance();
	/**
	  * Returns a QString pointer to the directory
	  */
	QString * getPath();

signals:

public slots:

private:

	TextShredderLogDir(QObject *parent);
    static TextShredderLogDir * dirInstance;
    QString DirPath;
};

#endif // TEXTSHREDDERLOGDIR_H
