//@author A0118904E

#ifndef ADD_H
#define ADD_H

#include "Task.h"
#include "Command.h"
#include "Storage.h"
#include "Delete.h"
#include "RecurringTask.h"
#include <iostream>
#include <stdlib.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class Add: public Command {

private:
	Task T1;
	Storage S1;
	RecurringTask R1;

public:
	Add(Task,RecurringTask);
	~Add();
	int getMonthNumber(string);
	string getMonthFromNumber(int);
	int getDayNumber(string);
	string execute(string,string); 
	string executeUndo(string,string);
	
};

#endif
