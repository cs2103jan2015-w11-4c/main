#include "Parser.h"
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;


const string CommandParser::commandIndicator = " ";
const string CommandParser::startDateIndicator = " on ";
const string CommandParser::startDayIndicator = "/";
const string CommandParser::startTimeIndicator = " at ";
const string CommandParser::currentYear = "2015";
const string CommandParser::endTimeIndicator = " by ";
const string CommandParser::hourIndicator = ":.";



const int CommandParser::startingPosition = 0;
const int CommandParser::positionModerator1 = 1;
const int CommandParser::positionModerator2 = 2;

string CommandParser::userInput = "";
string CommandParser::startDate = "";
string CommandParser::startTime = "";
string CommandParser::endDate = "";


//vector<string> CommandParser::parsedInput;
//Command::CommandType CommandParser::_command = Command::CommandType::TASKINVALID;



/*Command::CommandType Command::stringToCommandType(string command) {
	if (isExit(command)) {
		return Command::CommandType::EXIT;
	}
	if (isAdd(command)) {
		return Command::CommandType::TASKADD;
	}
	if (isDelete(command)) {
		return Command::CommandType::TASKDELETE;
	}
	if (isUpdate(command)) {
		return Command::CommandType::TASKUPDATE;
	}
	if (isDisplay(command)) {
		return Command::CommandType::TASKDISPLAY;
	}
}*/


/*string CommandTypeToString(Command::CommandType cmd) {
	switch (cmd) {
	case Command::CommandType::EXIT:
		return Command::COMMAND_EXIT;
	case Command::CommandType::TASKADD:
		return Command::COMMAND_ADD;
	case Command::CommandType::TASKDELETE:
		return Command::COMMAND_DELETE;
	case Command::CommandType::TASKUPDATE:
		return Command::COMMAND_UPDATE;

	default:
		return Command::COMMAND_INVALID;
	}
}*/

/*bool Utility::isExit(string command) {
	return (command.compare(Command::COMMAND_EXIT) == SAME);
}
bool Utility::isAdd(string command) {
	return (command.compare(Command::COMMAND_ADD) == SAME);
}
bool Utility::isDelete(string command) {
	return (command.compare(Command::COMMAND_DELETE) == SAME);
}
bool Utility::isUpdate(string command) {
	return (command.compare(Command::COMMAND_UPDATE) == SAME);
}
bool Utility::isDisplay(string command) {
	return (command.compare(Command::COMMAND_DISPLAY) == SAME);
}*/



string Command::getCommand(string input){
	string cmd = input.substr(startingPosition, input.find(commandIndicator));
	Command::CommandType command = Command::stringToCommandType(C1);
	Task taskDetails;

	if(command=="Add") {
		Add *A1;
		A1=new Add(taskDetails);
		taskDetails.T1 setDescription(string description);
		taskDetails.T1 setDate(string startDate);
		taskDetails.T1 setMonth(string month);
		taskDetails.T1 setYear(string year);
		CommandType C1(A1);
		return C1;
	}
	else if(command=="Display") {
		Display *D1;
		D1 = new Display();
		CommandType C1(D1);
		return C1;
	}
	else if(command=="delete") {
		taskDetails.setNumber(userInput);
		Delete *Del;
		Del = new Delete(taskDetails);
		taskDetails.T1 setDescription(string description);
		taskDetails.T1 setDate(string startDate);
		taskDetails.T1 setMonth(string month);
		taskDetails.T1 setYear(string year);
		CommandType C1(Del);
		return C1;
	
	}	
	else if(command=="update") {
		int start = startIndex(userInput);
		int end = endIndex(userInput);
		taskDetails.setUpdated(userInput.substr(end+1)); 
		taskDetails.setNumber(userInput.substr(start,end-start));
		Update *U1;
		U1 = new Update(taskDetails);
		taskDetails.T1 setDescription(string description);
		taskDetails.T1 setDate(string startDate);
		taskDetails.T1 setMonth(string month);
		taskDetails.T1 setYear(string year);
		CommandType C1(U1);
		return C1;
}
	else if(command=="Clear") {
		Clear *C2;
		C2 = new Clear();
		CommandType C1(C2);
		return C1;
	}
}


CommandParser::userInput = ui; 

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


string CommandParser::getStartTime(){

	try {
		if (startTime == CommandParser::NOT_EXIST) {
			return CommandParser::NOT_EXIST;
		}
		if (startTime.find_first_of(hourIndicator)==string::npos) {
			return startTime;
		}
		else {
			return startTime.substr(startingPosition,startTime.find_first_of(hourIndicator));
		}
	} catch (exception &) {
		return CommandParser::NOT_EXIST;
	}
}

string CommandParser::getStartYear() {
	if (startDate == CommandParser::NOT_EXIST) {
		return CommandParser::NOT_EXIST;
	} else {

		if (startDate.find_first_of(startDayIndicator) == startDate.find_last_of(startDayIndicator)){ 
			return currentYear;
		}
		string year = startDate.substr(startDate.find_last_of(startDayIndicator),
			startDate.size() - startDate.find_last_of(startDayIndicator));
		startDate = startDate.substr(startingPosition,startDate.find_last_of(startDayIndicator));
		return year;
	}
}

string CommandParser::getStartMonth() {
	
	if (startDate == CommandParser::NOT_EXIST) {
		return CommandParser::NOT_EXIST;
	}
	string month = startDate.substr(startDate.find_first_of(startDayIndicator)+positionModerator1,
		startDate.find_last_of(startDayIndicator) - startDate.find_first_of(startDayIndicator)-positionModerator1);
	startDate = startDate.substr(startingPosition,startDate.find_first_of(startDayIndicator));
	return month;
}

string CommandParser::getDescription(string input) {
	return CommandParser::NOT_EXIST;
}


//same for getStartTime/Location/EndDate/Description

//vector <string> CommandParser::parsedInput;

/*vector<string> CommandParser::getParsedUserInput(string input){

	vector<string> CommandParser::parsedInput(Task::ATTR::SIZE);
	CommandParser::parsedInput[Task::ATTR::COMMAND] = CommandParser::getCommand(input);

	return CommandParser::parsedInput;
}*/

#endif