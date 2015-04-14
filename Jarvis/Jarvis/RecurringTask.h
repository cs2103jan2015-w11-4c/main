//@author A0118904E
#ifndef RECURRING_TASK
#define RECURRING_TASK

#include "Task.h"
using namespace std;

class RecurringTask: public Task {

private:
	bool isRecurring;
	bool isRecurringError;
	string taskDay;
	string startDate;
	string startMonth;
	string startYear;
	string period;
	string endDate;
	string endMonth;
	string endYear;
	string keyword;
	string recurringWord;
	

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
	void setWord(string);
	string getWord();
	void setRecWord(string);
	string getRecWord();
	string getStartDate();
	void setStartDate(string);
	string getStartMonth();
	void setStartMonth(string);
	string getStartYear();
	void setStartYear(string);
	string getPeriod();
	void setPeriod(string);


};

#endif