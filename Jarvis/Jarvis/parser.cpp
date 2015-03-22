#include "Parser.h"


using namespace std;

string CommandParser::userInput = "";
const string INDENTIFIERS = "./?! ";
const string CommandParser::startDateIndicator = " on ";
const string CommandParser::endTimeIndicator = " by ";
/*const string CommandParser::commandIndicator = " ";

const string CommandParser::startDayIndicator = "/";
const string CommandParser::startTimeIndicator = " at ";
const string CommandParser::currentYear = "2015";

const string CommandParser::hourIndicator = ":.";



const int CommandParser::startingPosition = 0;
const int CommandParser::positionModerator1 = 1;
const int CommandParser::positionModerator2 = 2;


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

int CommandParser::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int CommandParser::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string CommandParser::extractUserCommand(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	userInput = input.substr(end+1); 
	return input.substr(start,end-start);
}

Task CommandParser::parseString(string userInput) {
	int start = userInput.find("on");
	string desc = userInput.substr(0,start);
	userInput = userInput.substr(start+3);
	int startDate = userInput.find_first_not_of(" ");
	userInput = userInput.substr(startDate);
	int endDate = userInput.find_first_of(" ");
	string date = userInput.substr(startDate,endDate-startDate);
	userInput = userInput.substr(endDate+1);
	Task T1;
	T1.setDate(date);
	T1.setDescription(desc);
	T1.setMonth(userInput);
	//T1.setYear();
	return T1;
}

Task CommandParser::parserUpdate(string userInput){
	int startLine = userInput.find_first_not_of(" ");
	userInput = userInput.substr(startLine);
	int endLine = userInput.find_first_of(" ");
	string number = userInput.substr(0,endLine);
	userInput = userInput.substr(endLine+1);
	int startString = userInput.find_first_not_of(" ");
	userInput = userInput.substr(startString);
	Task T1;
	T1.setNumber(number);
	T1.setUpdated(userInput);
	return T1;

}
CommandType CommandParser::getParserInput(string input){
	Task taskDetails; 
	string command;
	command = extractUserCommand(input);

	//eg add lunch with mom on 16 feb
	// command now equals "add"
	//userInput stores " lunch with mom on 16 feb"

	if(command=="add") {
		taskDetails = parseString(userInput);
		Add *A1;
		A1=new Add(taskDetails);
		CommandType C1(A1);
		return C1;
	}
	else if(command=="display") {
		if(userInput!="")
			taskDetails.setKeywords(userInput);
		Display *D1;
		D1 = new Display(taskDetails);
		CommandType C1(D1);
		return C1;
	}
	else if(command=="delete") {
		taskDetails.setNumber(userInput);
		Delete *Del;
		Del = new Delete(taskDetails);
		CommandType C1(Del);
		return C1;
	
	}	
	else if(command=="update") {
		taskDetails = parserUpdate(userInput);
		Update *U1;
		U1 = new Update(taskDetails);
		CommandType C1(U1);
		return C1;
}
	else if(command=="clear") {
		Clear *C2;
		C2 = new Clear();
		CommandType C1(C2);
		return C1;
	}
	else if(command=="exit") {
		WrongFormat *W1;
		W1 = new WrongFormat();
		CommandType C1(W1);
		return C1;
	}
	else if(command=="search") {
		taskDetails.setKeywords(userInput);
		Search *S1;
		S1 = new Search(taskDetails);
		CommandType C1(S1);
		return C1;
	}
	else {
		WrongFormat *W1;
		W1 = new WrongFormat();
		CommandType C1(W1);
		return C1;
	}
}


/*CommandParser::userInput = ui; 

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

