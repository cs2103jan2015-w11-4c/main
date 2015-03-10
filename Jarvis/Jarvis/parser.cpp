#include "Parser.h"
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

const string CommandParser::UpdateIndicator = " to ";
const string CommandParser::commandIndicator = " ";


const int CommandParser::positionModerator1 = 1;

string CommandParser::userInput = "";

//vector<string> CommandParser::parsedInput;

//CommandParser::userInput = ui; 

string CommandParser::getUpdate(string input){
	try {
		unsigned int start = userInput.find_first_of(UpdateIndicator);
		start += positionModerator1;
		return input.substr(start input.size()-start);
		} catch (exception &) {
		return CommandParser::NOT_EXIST;
	}
}


//same for getStartTime/Location/EndDate/Description

//vector <string> CommandParser::parsedInput;

vector<string> CommandParser::getParsedUserInput(string input){

	//vector<string> CommandParser::parsedInput(Task::ATTR::SIZE);
	//CommandParser::parsedInput[Task::ATTR::COMMAND] = CommandParser::getCommand(input);

	return CommandParser::ParsedUserInput;
}

#endif
