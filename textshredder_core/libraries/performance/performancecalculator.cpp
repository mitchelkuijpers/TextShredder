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
}

void PerformanceCalculator::addNewLockTime(uint lockTime) {
	this->lockingTimes.append(lockTime);
	reCalculateAverageLockTime();
	emit newAverage(this->lockingTimeAverage);
	qDebug() << "average locktime: " << this->lockingTimeAverage;
}

void PerformanceCalculator::reCalculateAverageLockTime() {
	int totalCount = this->lockingTimes.count();
	int total = 0;
	int i = 0;
	for(i =0; i < totalCount; i++) {
		total += this->lockingTimes.at(i);
	}
	this->lockingTimeAverage = total / totalCount;
}

long PerformanceCalculator::getAverage() {
	return this->lockingTimeAverage;
}
