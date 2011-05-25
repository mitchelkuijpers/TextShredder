#include "performancecalculator.h"


PerformanceCalculator* PerformanceCalculator::sharedInstance = NULL;

PerformanceCalculator * PerformanceCalculator::Instance()
{
	if (!sharedInstance ) {
		sharedInstance = new PerformanceCalculator(NULL);
	}
	return sharedInstance;
}

PerformanceCalculator::PerformanceCalculator(QObject * parent) :
QObject(parent)
{
	this->lockingTimeAverage = 0;
	timer.setInterval(PERFORMANCE_INTERVAL);
	timer.start();
	connect(&timer, SIGNAL(timeout()), this, SLOT(sendSignals()));
}

void PerformanceCalculator::addNewLockTime(uint lockTime) {
	this->lockingTimes.prepend(lockTime);
	reCalculateAverageLockTime();
}

void PerformanceCalculator::reCalculateAverageLockTime() {
	mutex.lock();
	float total = 0;
	int i = 0;
	int maxLocktimes = MAX_LOCKTIMES;
	while(this->lockingTimes.count() > maxLocktimes) {
		this->lockingTimes.removeLast();
	}
	for(i = 0; i < this->lockingTimes.count(); ++i) {
		total += this->lockingTimes.at(i);
	}
	this->lockingTimeAverage = total / this->lockingTimes.count();
	mutex.unlock();
}

void PerformanceCalculator::sendSignals() {
	float invertedPercentage = 0;
	emit newAverage(this->lockingTimeAverage);
	if(this->lockingTimeAverage < 8) {
		float percentageStep = 100/8;
		float percentage = this->lockingTimeAverage * percentageStep;
		invertedPercentage = 100 - percentage;
	}
	emit newAveragePercentage(invertedPercentage);
}
