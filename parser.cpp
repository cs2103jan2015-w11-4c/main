#include "Parser.h"
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;


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

const int CommandParser::startingPosition = 0;
const int CommandParser::positionModerator1 = 1;
const int CommandParser::positionModerator2 = 2;
const int CommandParser::positionModerator3 = 3;
const int CommandParser::positionModerator4 = 4;

string CommandParser::userInput = "";
string CommandParser::startDate = "";
string CommandParser::startTime = "";
string CommandParser::endDate = "";
string CommandParser::location = "";
string CommandParser::name="";
vector<string> CommandParser::parsedInput;

CommandParser::userInput = ui; 

string CommandParser::getCommand(string input){
	string cmd = input.substr(startingPosition, input.find(commandIndicator));
	Calendar::COMMAND_TYPE command = Utility::stringToCOMMAND_TYPE(cmd);
	CommandParser::_command = command;

	if (Utility::isValidCommand(command)) { //if the command is a valid command type, return it. else return "add"
		return cmd;
	}
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
string CommandParser::getEndDate(string input){
	try {
		unsigned int start = input.rfind(endDateIndicator);
		if (start == string::npos) {
			return CommandParser::NOT_EXIST;
		}
		start += positionModerator4;
		endDate = input.substr(start, input.size() - start);
		return endDate;
	} catch (exception &) {
		return CommandParser::NOT_EXIST;
	}
}

string CommandParser::getKeywords(string input) {

	try {
		unsigned int start = userInput.find_first_of(commandIndicator);
		start += positionModerator1;
		return input.substr(start, input.size()-start);
	} catch (exception &) {
		return CommandParser::NOT_EXIST;
	}
}
string CommandParser::getDescription(string input) {
	return CommandParser::NOT_EXIST;
}


//same for getStartTime/Location/EndDate/Description

vector<string> CommandParser::getParsedUserInput(string input){

	vector<string> parsedInput(Task::ATTR::SIZE);
	parsedInput[Task::ATTR::COMMAND] = getCommand(input);

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
		parsedInput[Task::ATTR::NAME] = getName(input);
		parsedInput[Task::ATTR::DESCRIPTION] = getDescription(input);
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

#endif