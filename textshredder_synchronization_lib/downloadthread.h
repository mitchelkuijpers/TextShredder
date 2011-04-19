#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>


class DownloadThread : public QThread
{
	Q_OBJECT
public:
	DownloadThread(QObject *parent);

signals:

public slots:

private:
	void run();
};

#endif // DOWNLOADTHREAD_H
