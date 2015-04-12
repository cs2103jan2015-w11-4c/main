#include "Update.h"
#include <sstream>
#include <iostream>

#include <queue>
using namespace std;


const string INDENTIFIERS = ".,!? ";
string Update::originalTask;
string Update::updatedTask;
const string ERROR_PREVIOUS_COMMAND = "Error: Please view your task list using the *DISPLAY* command before deleting a task\n";
const string DISPLAY_COMMAND = "display";
const string TASK_UPDATE = "task";
const string DATE_UPDATE = "date";
const string TIME_UPDATE = "time";
const string ERROR_UPDATE_LINE = "Error: Please enter a valid task number.\nThe update format is: *update <task number> <category> <update line>*\n";
const string ERROR_UPDATE_CATEGORY = "Error: Please enter a valid category to update.\nCategory: task, date, time\n";
const string ERROR_UPDATE_FORMAT = "Error: Please enter the correct format for update.\nThe update format is: *update <task number> <category> <update line>*\n";
const string ERROR_UPDATE_TASK_LINE = "Error: Update to task name unsuccessful.\nNo task exists at the line number ";
const string ERROR_UPDATE_DATE = "Error: Please enter a correct date to update the task. Press the *?* to view the command formats";
const string ERROR_PASSED_DATE = "Error: A task cannot be added in the past. Please enter a date more than the current date";
const string TIME_KEYWORD = "to";
const string ERROR_TIME_PERIOD = "Error: The end time of the task should be more than the start time of the task\n";
const string ERROR_UPDATE_TIME = "Error: Please enter a correct time to update the task. Press the *?* to view the command formats"; 

Update::Update(Task TaskAttributes) {
	T1=TaskAttributes;
}

Update::~Update() {

}

int Update::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int Update::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string Update::extractLineNumber(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	return input.substr(end+2); 
}

bool Update::isValidCommand(string input) {
	if(input==DISPLAY_COMMAND) {
		return true;
	} else {
		return false;
	}
}

int Update::getLineNumber(vector <string> tokens) {
	Logic L1;
	string number = L1.correctNumber(tokens[0]);
	return convertStringToInt(number);
}

int Update::convertStringToInt(string s) {
	try {
		int value = stoi(s);
		return value;
	}
	catch (const std::invalid_argument) {
		return 0;
	}
}


string Update::getCategory(vector<string> tokens) {
	string category;
	if(tokens[1]==TASK_UPDATE || tokens[1]==DATE_UPDATE || tokens[1]==TIME_UPDATE)
		return tokens[1];
	else
		return "";

}

bool Update::updateTask(string fileData, int userLine, string category, vector <string> tokens,string& newFileData,string& originalData) {
	string taskDesc="";
	int i;
		if(tokens.size()>2){
			isWrongTaskFormat=false;
			for(i=2;i<tokens.size()-1;i++) {
				taskDesc = taskDesc + tokens[i] + " ";
			}
			if(i==tokens.size()-1) {
				taskDesc = taskDesc + tokens[i];
			}
		}
		else {
			isWrongTaskFormat=true;

		}
	vector <string> originalTokens;
	
	bool statusOfUpdate=false;
	istringstream file(fileData);
	string lineFromFile;
	int lineNumber=1;
	if(!isWrongTaskFormat) {
		while(getline(file,lineFromFile)) {
			if(!lineFromFile.empty()) {
				if(userLine==lineNumber) {
					boost::split(originalTokens, lineFromFile,boost::is_any_of("/"));
					T1.setDescription(taskDesc);
					originalTokens[0]=taskDesc;
					newFileData = T1.getDescription() + "/" + originalTokens[1] + "/" +  lowerCase((originalTokens[2]).substr(0,3)) + "/" + originalTokens[3] +  "/" + originalTokens[4] + "/" + originalTokens[5] + "/" + originalTokens[6] + "/" + originalTokens[7] + "/" + originalTokens[8] + "/" + originalTokens[9] + "/" + originalTokens[10] +"\n";
					originalData = lineFromFile;
					statusOfUpdate=true;
					break;
				}
			}
			lineNumber++;
		}
	return statusOfUpdate;
	}
	else {
		return false;
	}
	
}

int Update::getMonthNumber(string monthName) {
	if(monthName.size()<3) {
		return 0;
	}
	map<string, int> months;
	map<string,int>::iterator iter;

		months["jan"]=1;
		months["feb"]=2;
		months["mar"]=3;
		months["apr"]=4;
		months["may"]=5;
		months["jun"]=6;
		months["jul"]=7;
		months["aug"]=8;
		months["sep"]=9;
		months["oct"]=10;
		months["nov"]=11;
		months["dec"]=12;

	 iter = months.find(monthName.substr(0,3));

	if (iter != months.end())
		return iter->second;
	return 0;
}


bool Update::checkDateMonth(string date, string month) {
	int taskDate = convertStringToInt(date);
	int taskMonth = getMonthNumber(month);
	int taskYear = 2015;
	try {
		boost::gregorian::date userDate(taskYear, taskMonth, taskDate);
		ptime now = microsec_clock::local_time();
		boost::gregorian::date today = now.date();
		if(userDate<today) {  //Date is not valid since its before the current date.
			isDatePassed=true;
			return false;

		}
		else {  //Date is valid
			isDatePassed=false;
			isWrongDateFormat=false;
			return true;
		}
	}
	catch (std::out_of_range) {    ///Date is not valid because tokens are not valid
		isWrongDateFormat=true;
		return false;
	}

}

bool Update::checkDateMonthYear(string date, string month, string year) {
	int taskDate = convertStringToInt(date);
	int taskMonth = getMonthNumber(month);
	int taskYear = convertStringToInt(year);
	try {
		boost::gregorian::date userDate(taskYear, taskMonth, taskDate);
		ptime now = microsec_clock::local_time();
		boost::gregorian::date today = now.date();
		if(userDate<today) {  //Date is not valid since its before the current date.
			isDatePassed=true;
			return false;

		}
		else {  
			isDatePassed=false;      //Date is valid
			return true;
		}
	}
	catch (std::out_of_range) {    ///Date is not valid because tokens are not valid
		return false;
	}
}

bool Update::updateDate(string fileData, int userLine, string category, vector <string> tokens,string& newFileData,string& originalData) {
	string taskDesc="";
	int i;
		if(tokens.size()==5){
			if(checkDateMonthYear(tokens[2],tokens[3],tokens[4])){
				T1.setYear(tokens[4]);
				isWrongDateFormat=false;
			}
			else {
				isWrongDateFormat=true;
			}
		}
		else if(tokens.size()==4) {
			if(checkDateMonth(tokens[2],tokens[3])){
				T1.setYear("2015");
				isWrongDateFormat=false;
			}
			else {
				isWrongDateFormat=true;
			}

		}
		else {

			isWrongDateFormat=true;
		}
			vector <string> originalTokens;
			bool statusOfUpdate=false;
			istringstream file(fileData);
			string lineFromFile;
			int lineNumber=1;
			if(!isWrongDateFormat) {
			while(getline(file,lineFromFile)) {
				if(!lineFromFile.empty()) {
					if(userLine==lineNumber) {
						boost::split(originalTokens, lineFromFile,boost::is_any_of("/"));
						T1.setDate(tokens[2]);
						T1.setMonth(tokens[3]);
						newFileData = originalTokens[0] + "/" + T1.getDate() + "/" +  lowerCase((T1.getMonth()).substr(0,3)) + "/" + T1.getYear() +  "/" + originalTokens[4] + "/" + originalTokens[5] + "/" + originalTokens[6] + "/" + originalTokens[7] + "/" + originalTokens[8] + "/" + originalTokens[9] + "/" + originalTokens[10] +"\n";
						cout << newFileData << endl;
						originalData = lineFromFile;
						statusOfUpdate=true;
						break;
					}
				}
				lineNumber++;
			}
	return statusOfUpdate;
	}
	else {
		return false;
	}
	
}

bool Update::isHourValid(string hour) {
	try{
		int number = stoi(hour);
		if(number>=0 && number<=23){
			return true;
		}
		else
			return false;
	}
	catch(const std::invalid_argument) {

		return false; 

	}
}

bool Update::isMinuteValid(string minute) {
	try{
		int number = stoi(minute);
		if(number>=0 && number<=59){
			return true;
		}
		else
			return false;
	}
	catch(const std::invalid_argument) {

		return false; 

	}
}

bool Update::checkByTime(string deadlineTime, string& hour, string& minute) {
	vector<string> timeTokens;
	isInvalidTimePeriod=false;
	boost::split(timeTokens,deadlineTime, boost::is_any_of(":"));
	if(timeTokens.size()==2) {
		if(isHourValid(timeTokens[0]) && isMinuteValid(timeTokens[1])) {
			hour=timeTokens[0];
			minute=timeTokens[1];
			return true;
		}
	}
	else {
		return false;
	}
}

bool Update::checkTime(string startTime, string keyword, string endTime,string& startHour, string& startMin, string& endHour, string& endMin) {
	if(keyword==TIME_KEYWORD) {
		vector<string> startTimeTokens;
		boost::split(startTimeTokens,startTime, boost::is_any_of(":"));
		vector <string> endTimeTokens;
		boost::split(endTimeTokens,endTime,boost::is_any_of(":"));
		if(startTimeTokens.size()==2 && endTimeTokens.size()==2 && isHourValid(startTimeTokens[0]) && isMinuteValid(startTimeTokens[1]) && isHourValid(endTimeTokens[0]) && isMinuteValid(endTimeTokens[1])) {
			startHour=startTimeTokens[0];
			startMin=startTimeTokens[1];
			endHour=endTimeTokens[0];
			endMin=endTimeTokens[1];
			if(stoi(endHour)>stoi(startHour))
				return true;
			else if(stoi(endHour)==stoi(startHour)) {
				if(stoi(endMin)>stoi(startMin)){
					return true;
				}
				else {
					isInvalidTimePeriod=true;
					return false;
				}
			}
			else {
				isInvalidTimePeriod=true;
				return false;
			}
		}
		else {
			return false;
		}

	}
	else {
		return false;
	}
}

bool Update::updateTime(string fileData, int userLine, string category, vector <string> tokens,string& newFileData,string& originalData) {
	string hour="",min="",startHour="",startMin="",endHour="",endMin="";
	int i;
	if(tokens.size()==3){
		if(checkByTime(tokens[2],hour,min)) {
			T1.setHour(hour);
			T1.setMinute(min);
			isWrongTimeFormat=false;
		}
		else {
			isWrongTimeFormat=true;
		}
	}
	else if(tokens.size()==5) {
		if(checkTime(tokens[2],tokens[3],tokens[4],startHour,startMin,endHour,endMin)){
			T1.setStartHour(startHour);
			T1.setStartMinute(startMin);
			T1.setEndHour(endHour);
			T1.setEndMinute(endMin);
			isWrongTimeFormat=false;
		}
		else {
			isWrongTimeFormat=true;
		}
	}
	else {
		isWrongTimeFormat=true;
	}
	vector <string> originalTokens;
	bool statusOfUpdate=false;
	istringstream file(fileData);
	string lineFromFile;
	int lineNumber=1;
	if(!isWrongTimeFormat) {
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(userLine==lineNumber) {
				boost::split(originalTokens, lineFromFile,boost::is_any_of("/"));
				newFileData = originalTokens[0] + "/" + originalTokens[1] + "/" +  lowerCase((originalTokens[2]).substr(0,3)) + "/" + originalTokens[3] +  "/" + T1.getHour() + "/" + T1.getMinute() + "/" + T1.getStartHour() + "/" + T1.getStartMinute() + "/" +  T1.getEndHour() + "/" +  T1.getEndMinute() + "/" + originalTokens[10] +"\n";
				cout << newFileData << endl;
				originalData = lineFromFile;
				statusOfUpdate=true;
				break;
			}
		}
		lineNumber++;
	}
	cout << userLine << endl;
	return statusOfUpdate;
	}
	else {
		return false;
	}
	
}


string Update::execute(string fileName,string filePath) {
	CommandParser P1;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	if(commandStack.empty()) {
		return ERROR_PREVIOUS_COMMAND;
	}
	string lastInput = commandStack.top();
	CommandType C1 = P1.getParserInput(lastInput,commandStack);
	string command = P1.getCommand();
	if(!isValidCommand(command)) {
		return ERROR_PREVIOUS_COMMAND;
	}
	string fileData = C1.run(fileName,filePath);
	vector <string> tokensToUpdate = T1.getUpdateTokens();
	if(tokensToUpdate.size()<3) {
		return ERROR_UPDATE_FORMAT;
	}
	int userLine = getLineNumber(tokensToUpdate);
	string category = getCategory(tokensToUpdate);
	string newFileData;
	string originalData;
	if(userLine==0) {
		return ERROR_UPDATE_LINE;
	}
	if(category=="") {
		return ERROR_UPDATE_CATEGORY;
	}
	if(category==TASK_UPDATE) {
		bool isTaskUpdate = updateTask(fileData,userLine,category,tokensToUpdate,newFileData,originalData);
		if(isWrongTaskFormat) {
			return ERROR_UPDATE_FORMAT;
		}
		else {
			if(isTaskUpdate) {
				performUpdate(originalData,newFileData,fileName,filePath);
				return "Description of task " + to_string(userLine) + " updated to *" + T1.getDescription() + "*\n";
			}
			else {
				return ERROR_UPDATE_TASK_LINE + to_string(userLine);
			}
		}
	}
	else if(category==DATE_UPDATE) {
		bool isDateUpdate =	updateDate(fileData,userLine,category,tokensToUpdate,newFileData,originalData);
		if(isDatePassed) {
			return ERROR_PASSED_DATE;
		}
		else if(isWrongDateFormat) {
			return ERROR_UPDATE_DATE;
		}
		else {
			if(isDateUpdate) {
				performUpdate(originalData,newFileData,fileName,filePath);
				return "Date of task " + to_string(userLine) + " updated to *" + T1.getDate() + " " + T1.getMonth() + " " + T1.getYear() +" *\n";
			}
			else {
				return ERROR_UPDATE_TASK_LINE + to_string(userLine);
			}
		}
	
	
	}
	else {
		bool isTimeUpdate = updateTime(fileData,userLine,category,tokensToUpdate,newFileData,originalData);
		//if(isInvalidTimePeriod) {
			//return ERROR_TIME_PERIOD;
		//}
		if(isWrongTimeFormat) {
			return ERROR_UPDATE_TIME;
		}
		else {
			if(isTimeUpdate) {
				performUpdate(originalData,newFileData,fileName,filePath);
				return "Time of task " + to_string(userLine) + " updated\n";
			}
			else {
				return ERROR_UPDATE_TASK_LINE + to_string(userLine);
			}
		}
	
	
	}
	
}
	

void Update::performUpdate(string originalData, string newFileData, string fileName, string filePath) {
	Storage S1;
	bool update = S1.updateFileData(originalData,newFileData,fileName,filePath);
	setOriginalTask(originalData);
	setUpdatedTask(newFileData);

}

void Update::setOriginalTask(string task) {
	originalTask = task;
}

string Update::getOriginalTask() {
	return originalTask;
}

void Update::setUpdatedTask(string task) {
	updatedTask = task;
}

string Update::getUpdatedTask() {
	return updatedTask;
}

string Update::lowerCase(string input) {

	transform(input.begin(), input.end(), input.begin(), ::tolower);

	return input;
}

