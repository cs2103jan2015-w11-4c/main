#include "Parser.h"
#include <boost/algorithm/string.hpp>

using namespace std;

//string CommandParser::userInput = "";
const string INDENTIFIERS = "./?! ";
const string CommandParser::startDateIndicator = " on ";
const string CommandParser::endTimeIndicator = " by ";
const string CommandParser::hourIndicator = ":";
const string CommandParser::startTimeIndicator = "from";
const string CommandParser::deadlineTimeIndicator = "to";
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
Task CommandParser::getTaskObject() {
	return taskDetails;
}

string CommandParser::getUserInput() {
	return userInput;
}

int CommandParser::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int CommandParser::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string CommandParser::changeToLowerCase(string input) {
	string lowerCase="";
	for(int i=0;i<input.size();i++) {
		if(input[i]>='A' && input[i]<='Z') {
			input[i] = tolower(input[i]);
			lowerCase = lowerCase + input[i];
		}
		else {
			lowerCase = lowerCase + input[i];
		}
	}
	return lowerCase;
}

string CommandParser::extractUserCommand(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	userInput =input.substr(end+1);

	return input.substr(start,end-start);
}

int CommandParser::findKeywordPosition(string searchString, string keyWord) {
	int lenString = searchString.size();
	int lenWord = keyWord.size();
	std::string::iterator it(searchString.begin()), end(searchString.end());
	std::string::iterator s_it(keyWord.begin()), s_end(keyWord.end());
	it = std::search(it, end, s_it, s_end);

	while(it!=(end-1))
{
	if(searchString.at(*(it-1)==' ') && searchString.at(*(it+lenWord)==' ')) {
		return distance(searchString.begin(),it);
	}
	else
		advance(it, distance(s_it, s_end));
		it = search(it, end, s_it, s_end);

}

		return 0;


}

bool CommandParser::isMonth(string input) {
	if(input=="january" || input=="february" || input=="march" ||  input=="april" ||  input=="may" ||  input=="june" ||  input=="july" || input=="august" ||  input=="september" ||  input=="october" ||  input=="november" ||  input=="december")
		return true;
	else
		return false;
}



Task CommandParser::parseString(string userInput) {
	string desc;
	string date;
	string month;
	string hour;
	string minute;
	string StartHour;
	string StartMinute;
	string EndHour;
	string EndMinute;
	string str = "on";
	userInput = changeToLowerCase(userInput);
	boost::trim(userInput);
	int start = userInput.find(str);
	Task T1;
	if(start==string::npos) {
		T1.setDescription(userInput);
	}
	else {
		start = findKeywordPosition(userInput,str);
		if(start==0) {
			T1.setDescription(userInput);
			T1.setYear("");
			return T1;
		}
		else {
			desc = userInput.substr(0,start);
			userInput = userInput.substr(start+3);
			int startDate = userInput.find_first_not_of(" ");
			userInput = userInput.substr(startDate);
			int endDate = userInput.find_first_of(" ");
			date = userInput.substr(startDate,endDate-startDate);
			userInput = userInput.substr(endDate+1);
			int endMonth = userInput.find_first_of(" ");
			month = userInput.substr(0,endMonth);
			T1.setDate(date);
			T1.setDescription(desc);
			T1.setMonth(month);
			if(endMonth==userInput.size()) {
				return T1;
			}
			userInput = userInput.substr(endMonth+1);
			int keywordStart = userInput.find_first_not_of(" ");
			userInput = userInput.substr(keywordStart);
			int keywordEnd = userInput.find_first_of(" ");
			string word = userInput.substr(keywordStart,keywordEnd-keywordStart);
			if(word=="by") {
				userInput = userInput.substr(keywordEnd+1);
				hour = userInput.substr(0,userInput.find_first_of(":"));
				userInput = userInput.substr(userInput.find_first_of(":")+1);
				minute = userInput;

			}
			else if(word=="from") {
				userInput = userInput.substr(keywordEnd+1);
				StartHour = userInput.substr(userInput.find_first_not_of(" "),userInput.find_first_of(":")-userInput.find_first_not_of(" "));
				userInput = userInput.substr(userInput.find_first_of(":")+1);
				StartMinute = userInput.substr(0,userInput.find_first_of(" "));
				userInput = userInput.substr(userInput.find_first_of(" ")+1);
				int word2 = userInput.find("to");
				userInput = userInput.substr(word2+2);
				EndHour = userInput.substr(userInput.find_first_not_of(" "),userInput.find_first_of(":")-userInput.find_first_not_of(" "));
				userInput = userInput.substr(userInput.find_first_of(":")+1);
				EndMinute = userInput.substr(0,userInput.find_first_of(" "));
			}
			
			T1.setHour(hour);
			T1.setMinute(minute);
			T1.setStartHour(StartHour);
			T1.setStartMinute(StartMinute);
			T1.setEndHour(EndHour);
			T1.setEndMinute(EndMinute);
		}
		
		
		
	}
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
	Task T1 = parseString(userInput);
	Logic L1;
	T1.setNumber(L1.correctNumber(number));
	return T1;

}
CommandType CommandParser::getParserInput(string input,stack <string> inputStack){
	string command;
	boost::trim(input);
	command = extractUserCommand(input);
	command = changeToLowerCase(command);
	boost::trim(command);
	taskDetails.setStack(inputStack);
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
		Display *D1;
		//if(userInput!="") {
		taskDetails.setKeywords(userInput);
		D1 = new Display(taskDetails);
		//}
		//else {
			//D1 = new Display();
		//}
		CommandType C1(D1);
		return C1;
	}
	else if(command=="delete") {
		Logic L1;
		taskDetails.setNumber(L1.correctNumber(userInput));
		Delete *Del;
		Del = new Delete(taskDetails);
		CommandType C1(Del);
		return C1;
	
	}	
	else if(command=="update") {
		taskDetails = parserUpdate(userInput);
		taskDetails.setStack(inputStack);
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
	else if(command=="undo") {
		taskDetails.setKeywords(userInput);
		Undo *U1;
		U1 = new Undo(taskDetails);
		CommandType C1(U1);
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
