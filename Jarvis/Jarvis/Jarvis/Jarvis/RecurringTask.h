#ifndef RECURRING_TASK
#define RECURRING_TASK

#include "Task.h"
using namespace std;

class RecurringTask:public Task {

private:
	bool isRecurring;
	bool isRecurringError;
	string taskDay;
	string endDate;
	string endMonth;
	string endYear;


public:
	RecurringTask();
	~RecurringTask();
	string getTaskDay();
	void setTaskDay(string);
	string getEndDate();
	void setEndDate(string);
	string getEndMonth();
	void setEndMonth(string);
	string getEndYear();
	void setEndYear(string);
	bool getRecurring();
	void setRecurring(bool);
	bool getRecurringError();
	void setRecurringError(bool);




};

#endif