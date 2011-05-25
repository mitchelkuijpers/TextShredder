#ifndef PERFORMANCECALCULATOR_H
#define PERFORMANCECALCULATOR_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTimer>

#define MAX_LOCKTIMES 15;
#define PERFORMANCE_INTERVAL 1000

/**
  * Save averages of usefull performance information to show in the UI.
  */
class PerformanceCalculator : public QObject
{
	Q_OBJECT
public:

	/**
	  * Get an instance of the PerformanceCalculator singleton.
	  *
	  * @return An instance of the performance calculator.
	  */
	static PerformanceCalculator * Instance();

private:

	/**
	  * Private constructor because this is an singleton.
	  *
	  * @param parent The parent QObject object.
	  */
	PerformanceCalculator(QObject * parent);
	void reCalculateAverageLockTime();

	QMutex mutex;
	QTimer timer;
	QList<unsigned int> lockingTimes;
	static PerformanceCalculator * sharedInstance;
	float lockingTimeAverage;
signals:

	/**
	  * notifies that the average value has been updated.
	  */
	void newAverage(float);

	/**
	  * notifies that the average Percentage has been updated
	  */
	void newAveragePercentage(float invertedPercentage);

public slots:

	/**
	  * Adds a new locktime in an list, then recalculates the average locktime
	  *	over the last @value(MAX_LOCKTIMES) locktime(s).
	  *
	  * @param locktime time syncthread was locked.
	  */
	void addNewLockTime(uint);

	void sendSignals();
};

#endif // PERFORMANCECALCULATOR_H
