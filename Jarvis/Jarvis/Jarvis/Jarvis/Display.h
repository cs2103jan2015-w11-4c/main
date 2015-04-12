#ifndef DISPLAY_H
#define DISPLAY_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Search.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <map>
using namespace std;

class Display:public Command {

private:
	Storage S1;
	Task T1;

public:
	Display();
	Display(Task);
	~Display();
	string getFullMonth(string);
	int getDayNumber(string);
	string execute(string,string);
	int getMonthNumber(string);

};

#endif