//@author A0118904E
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "Command.h"
#include "CommandType.h"
#include "RecurringTask.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <vector>
#include <string>
#include "CommandType.h"
#include "Add.h"
#include "Display.h"
#include "Delete.h"
#include "Update.h"
#include "Clear.h"
#include "Search.h"
#include "Undo.h"
#include "WrongFormatCommand.h"
#include "Task.h"
#include "Done.h"
//#include "redo.h"
#include <algorithm>
#include <iterator>

using namespace std;



class CommandParser {

public:
	
	CommandParser();
	~CommandParser();
	CommandType getParserInput(string,stack <string>);
	string extractUserCommand(string);
	Task parseString(string,RecurringTask&);
	Task parserUpdate(string);
	string check(string);
	string trim(string const&);
	int findKeywordPosition(string, string);
	string getUserInput();
	Task getTaskObject();
	string changeToLowerCase(string input);
	bool isDeadlineTask(vector <string>,vector<string>&,Task&);
	int getMonthNumber(string);
	bool isHourValid(string);
	bool isMinuteValid(string);
	bool isDayValid(string);
	bool isTimeValid(boost::posix_time::time_duration,boost::gregorian::date);
	void findYear(vector <string>&, int, Task& T1 );
	int convertStringToInt(string);
	bool isDateValid(int, int, int);
	void findRecDate(vector <string>& , int, RecurringTask&);
	bool isPeriodValid(string);
	void setCommand(string);
	string getCommand();
	vector <string> trimUserInputTokens(string);
	bool isDateAfterToday (boost::gregorian::date);
	vector <string> convertTokensToLowerCase(vector <string>);

private:
	string userInput;
	string command;
	bool isWrongDate;
	bool dateValid;
	bool timedTask;
	bool floatingTask;
	bool deadlineTask;
	bool isYearValid;
	CommandType  C1;
	Task taskDetails; 
};

#endif
//header ends
