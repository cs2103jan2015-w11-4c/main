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
#include <algorithm>
#include <iterator>

using namespace std;



class CommandParser {
public:
	static const string NOT_EXIST;

	static string getCommand(string input);
	static string getStartYear();
	static string getStartMonth();
	static string getStartDay();
	static string getStartHour();
	static string getStartMinute();
	static string getEndYear(string input);
	static string getEndMonth(string input);
	static string getEndDay(string input);
	static string getEndHour(string input);
	static string getEndMinute(string input);
	static string getName(string input);
	static string getDescription(string input);
	static string getKeywords(string input);
	static vector <string> getParsedUserInput(string uInput);
	CommandType getParserInput(string,stack <string>);
	static string getStartDate(string input);
	static string getStartTime(string input);
	static string getEndDate(string input);
	void setUserInput(string ui);
	void setDate(string d);
	void setParserInput(vector <string> pi);
	string extractUserCommand(string);
	int startIndex(string);
	int endIndex(string);
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
private:
	string userInput;
	static string startDate;
	static string endDate;
	static string startTime;
	static string location;
	static string name;
	bool timedTask;
	bool floatingTask;
	bool deadlineTask;
	const static string commandIndicator;
	const static string startDateIndicator;
	const static string startDayIndicator;
	const static string startTimeIndicator;
	const static string spaceIndicator;
	const static string hourIndicator;
	const static string endDateIndicator;
	const static string endDayIndicator;
	const static string deadlineTimeIndicator;


	const static int startingPosition;
	const static int positionModerator1;
	const static int positionModerator2;
	const static string endTimeIndicator; 

	vector<string> parsedInput;
	static CommandType  C1;
	Task taskDetails; 
};

#endif
//header ends
