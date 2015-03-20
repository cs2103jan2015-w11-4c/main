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

string CommandParser::userInput = "";
string CommandParser::startDate = "";
string CommandParser::startTime = "";
string CommandParser::endDate = "";
string CommandParser::location = "";

vector<string> CommandParser::parsedInput;

Command::COMMAND_TYPE CommandParser::_command = Command::COMMAND_TYPE::TASKINVALID;


string CommandParser::getCommand(string input){
	string cmd = input.substr(startingPosition, input.find(commandIndicator)); 
	Command::COMMAND_TYPE command = Utility::stringToCOMMAND_TYPE(cmd);
	CommandParser::_command = command;

	if (Utility::isValidCommand(command)) { //if the command is a valid command type, return it. else return "add"
		return cmd;
	}
	return Command::COMMAND_ADD; 
}

CommandParser::userInput = ui; 

string CommandParser::getCommand(string input){
	string cmd = input.substr(startingPosition, input.find(commandIndicator));
	Command::COMMAND_TYPE command = Utility::stringToCOMMAND_TYPE(cmd);
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
		start += positionModerator1;
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
		start += positionModerator1;
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

//vector <string> CommandParser::parsedInput;

vector<string> CommandParser::getParsedUserInput(string input){

	vector<string> CommandParser::parsedInput(Task::ATTR::SIZE);
	CommandParser::parsedInput[Task::ATTR::COMMAND] = CommandParser::getCommand(input);

	return CommandParser::parsedInput;
}

#endif