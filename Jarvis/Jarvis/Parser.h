#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "Command.h"
#include "CommandType.h"

#include <vector>
#include <string>

using namespace std;

class Utility {
public:
	static bool stringToBool(string s);
	static string boolToString(bool b);
	static CommandType stringToCommandType(string command);
	static string CommandTypeToString(CommandType C1);
	static bool isValidCommand(CommandType C1);
	
private:
	static bool isExit(string command);
	static bool isAdd(string command);
	static bool isDelete(string command);
	static bool isUpdate(string command);
	static bool isDisplay(string command);
	
	static const int SAME;
};


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
	static string getPriority(string input);
	static string getName(string input);
	static string getDescription(string input);
	static string getLocation(string input);
	static string getKeywords(string input);
	static vector <string> getParsedUserInput(string uInput);

	static string getStartDate(string input);
	static string getStartTime(string input);
	static string getEndDate(string input);
	void setUserInput(string ui);
	void setDate(string d);
	void setParserInput(vector <string> pi);

private:
	static string userInput;
	static string startDate;
	static string endDate;
	static string startTime;
	static string location;
	static string name;

	const static string commandIndicator;
	const static string startDateIndicator;
	const static string startDayIndicator;
	const static string startTimeIndicator;
	const static string locationIndicatorStart;
	const static string locationIndicatorEnd;
	const static string spaceIndicator;
	const static string currentYear;
	const static string hourIndicator;
	const static string endDateIndicator;
	const static string endDayIndicator;

	const static int startingPosition;
	const static int positionModerator1;
	const static int positionModerator2;
	const static int positionModerator3;
	const static int positionModerator4;

	vector<string> parsedInput;
	static CommandType  C1;
};

#endif
//header ends

