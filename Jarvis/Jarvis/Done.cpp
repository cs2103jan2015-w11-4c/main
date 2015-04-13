#include "Done.h"
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <stack>
using namespace std;


const string INDENTIFIERS = ".,!? ";
string Done::originalDoneTask;
string Done::updatedDoneTask;
const string ERROR_PREVIOUS_COMMAND = "Error: Please view your task list using the *DISPLAY* command before marking a task as done";
const string DISPLAY_COMMAND = "display";

Done::Done(Task TaskAttributes) {
	T1=TaskAttributes;
}

Done::~Done() {

}

int Done::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int Done::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string Done::extractLineNumber(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	return input.substr(end+2); 
}

bool Done::isValidCommand(string input) {
	if(input==DISPLAY_COMMAND) {
		return true;
	} else {
		return false;
	}
}


string Done::execute(string fileName,string filePath) {
	CommandParser P1;
	string s;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	if(commandStack.empty()) {
		return ERROR_PREVIOUS_COMMAND;
	}
	string lastInput = commandStack.top();
	//Call parser to execute lastInput. It will return a command type object that I will execute to get a input string.
	CommandType C1 = P1.getParserInput(lastInput,commandStack);
	string command = P1.getCommand();
	if(!isValidCommand(command)) {
		return ERROR_PREVIOUS_COMMAND;
	}
	string input = C1.run(fileName,filePath);
	istringstream file(input);
	string lineFromFile;
	int lineNumber=1;
	string doneData="";
	vector <string> doneTokens;
	string newStatus;
	string userLine = T1.getNumber();
	if(userLine=="") {
		return "Error: Please enter *DONE* followed by the correct number of the task to be marked as done.\n";
	}
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())==lineNumber) {
				doneData = doneData + lineFromFile + "\n";
				boost::split(doneTokens,lineFromFile,boost::is_any_of("/"));
				doneTokens[10]="done";
			}

		}
		
		lineNumber++;
	}
	int i;
	for(i=0;i<doneTokens.size()-1;i++)
		newStatus = newStatus + doneTokens[i] + "/"; 
	if(i==doneTokens.size()-1)
		newStatus = newStatus + doneTokens[i] + "\n";
	if(doneData!="") {
		S1.updateFileData(doneData,newStatus,fileName,filePath);
		setOriginalDoneTask(doneData);
		setUpdatedDoneTask(newStatus);
		return "The task is marked as done";
	}
	
	else {
		return "Error: Please enter *DONE* followed by the correct number of the task to be marked as done";
	}

}

string Done::getOriginalDoneTask() {
	return originalDoneTask;
}
void Done::setOriginalDoneTask(string task) {
	originalDoneTask=task;
}

string Done::getUpdatedDoneTask() {
	return updatedDoneTask;
}

void Done::setUpdatedDoneTask(string task) {
	updatedDoneTask=task;
}