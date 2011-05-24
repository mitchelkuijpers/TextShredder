#ifndef PERFORMANCECALCULATOR_H
#define PERFORMANCECALCULATOR_H

#include <QObject>
#include <QDebug>

class PerformanceCalculator : public QObject
{
	Q_OBJECT
public:
	static PerformanceCalculator * Instance();
	long getAverage();

private:
	PerformanceCalculator(QObject * parent);
	void reCalculateAverageLockTime();

	QList<unsigned int> lockingTimes;
	static PerformanceCalculator * sharedInstance;
	long lockingTimeAverage;
signals:
	void newAverage(long);

public slots:
	void addNewLockTime(uint);
};

#endif // PERFORMANCECALCULATOR_H
