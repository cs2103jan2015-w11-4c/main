#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H


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
	static vector<string> getParsedUserInput(string uInput);

//header ends

#endif