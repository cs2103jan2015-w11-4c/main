#include "Parser.h"
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "Task.h"
#include "Calendar.h"
#include "Utility.h"

#include <string>
#include <vector>

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
	static string getPriority(string input);
	static string getName(string input);
	static string getDescription(string input);
	static string getLocation(string input);
	static string getKeywords(string input);
	static vector<string> getParsedUserInput(string uInput);

//header ends


const string CommandParser::commandIndicator = " ";
const string CommandParser::startDateIndicator = " on ";
const string CommandParser::startDayIndicator = "/";
const string CommandParser::startTimeIndicator = " at ";
const string CommandParser::locationIndicatorStart = " <";
const string CommandParser::locationIndicatorEnd = "> ";
const string CommandParser::currentYear = "2014";
const string CommandParser::hourIndicator = ":.";
const string CommandParser::endDateIndicator = " by ";
const string CommandParser::endDayIndicator = "/";

CommandParser::userInput = ui; 

string CommandParser::getCommand(string input){
	string cmd = input.substr(startingPosition, input.find(commandIndicator));
	Calendar::COMMAND_TYPE command = Utility::stringToCOMMAND_TYPE(cmd);
	CommandParser::_command = command;

	if (Utility::isValidCommand(command)) { //if the command is a valid command type, return it. else return "add"
		return cmd;
	}

string CommandParser::getStartDate(string input) {
	try {
		unsigned int start = input.rfind(startDateIndicator);
		if (start == string::npos) {
			return CommandParser::NOT_EXIST;
		}
		start += positionModerator4;
		startDate = input.substr(start, input.size() - start);
		return startDate;
	} catch (exception &) {
		return CommandParser::NOT_EXIST;
	}
}

//same for getStartTime/Location/EndDate/Description

vector<string> CommandParser::getParsedUserInput(string input){

	vector<string> parsedInput(Task::ATTR::SIZE);
	parsedInput[Task::ATTR::COMMAND] = getCommand(input);

	Calendar::COMMAND_TYPE cmd = Utility::stringToCOMMAND_TYPE(getCommand(input));

	switch (cmd) {
	case Calendar::COMMAND_TYPE::TASKADD:
		startDate = getStartDate(input);
		startTime = getStartTime(input);
		location = getLocation(input);
		name = getName(input);
		endDate = getEndDate(input);
		parsedInput[Task::ATTR::STARTYEAR] = getStartYear();
		parsedInput[Task::ATTR::STARTMONTH] = getStartMonth();
		parsedInput[Task::ATTR::STARTDAY] = getStartDay();
		parsedInput[Task::ATTR::STARTHOUR] = getStartHour();
		parsedInput[Task::ATTR::STARTMINUTE] = getStartMinute();
		parsedInput[Task::ATTR::ENDYEAR] = getEndYear(input);
		parsedInput[Task::ATTR::ENDMONTH] = getEndMonth(input);
		parsedInput[Task::ATTR::ENDDAY] = getEndDay(input);
		parsedInput[Task::ATTR::ENDHOUR] = getEndHour(input);
		parsedInput[Task::ATTR::ENDMINUTE] = getEndMinute(input);
		parsedInput[Task::ATTR::PRIORITY] = getPriority(input);
		parsedInput[Task::ATTR::NAME] = getName(input);
		parsedInput[Task::ATTR::DESCRIPTION] = getDescription(input);
		parsedInput[Task::ATTR::LOCATION] = getLocation(input);
		parsedInput[Task::ATTR::ISDONE] = "false";
		if (startDate == CommandParser::NOT_EXIST && endDate == CommandParser::NOT_EXIST) {
			parsedInput[Task::ATTR::HASDATE] = CommandParser::NOT_EXIST;
			parsedInput[Task::ATTR::HASEXPIRED] = CommandParser::NOT_EXIST;
		}
		else{
			parsedInput[Task::ATTR::HASDATE] = "true";
			parsedInput[Task::ATTR::HASEXPIRED] = "false";
		}
		break;
	case Calendar::COMMAND_TYPE::TASKEDIT:
		parsedInput.clear();
		parsedInput.resize(EDIT::LASTPOSITION);
		parsedInput[EDIT::SEARCH_KEYWORDS] = getKeywords(input);
		break;
	case Calendar::COMMAND_TYPE::TASKREMIND:
		parsedInput[REMIND::SEARCH_KEYWORDS] = getKeywords(input);
		break;
	case Calendar::COMMAND_TYPE::TASKREPEAT:
		parsedInput[REPEAT::SEARCH_KEYWORDS] = getKeywords(input);
		break;
	default:
		parsedInput[Task::ATTR::NAME] = getKeywords(input);
		break;
	}

	return parsedInput;
}
