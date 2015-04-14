//@author A0118904E
#include "Done.h"
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <stack>
using namespace std;

string Done::originalDoneTask;
string Done::updatedDoneTask;
const string ERROR_PREVIOUS_COMMAND = "Error: Please view your task list using the *DISPLAY* command before marking a task as done\n";
const string DISPLAY_COMMAND = "display";
const string ERROR_DONE = "Error: Please enter *DONE* followed by the correct number of the task to be marked as done.\n";
const string SUCCESS_DONE = "The task is marked as done\n";

Done::Done(Task TaskAttributes) {
	T1=TaskAttributes;
}

Done::~Done() {

}

//A user can only mark a task as done after a display command has been entered
bool Done::isValidCommand(string input) {
	if(input==DISPLAY_COMMAND) {
		return true;
	} else {
		return false;
	}
}


string Done::execute(string fileName,string filePath) {
	int i;
	CommandParser P1;
	string s;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	//The command stack stores all the inputs entered by the user since the program has started
	//If the stack is empty after removing this "done" command, the user is not allowed to delete.
	if(commandStack.empty()) {                        
		return ERROR_PREVIOUS_COMMAND;
	}
	string lastInput = commandStack.top();
	CommandType C1 = P1.getParserInput(lastInput,commandStack);
	string command = P1.getCommand();
	//The user can only mark a task as done after a display command
	if(!isValidCommand(command)) {
		return ERROR_PREVIOUS_COMMAND;
	}
	//retrieves the input specified by the last display command
	//If the user has entered display march, all the tasks in march are called so that he can mark done from this list
	string input = C1.run(fileName,filePath);
	istringstream file(input);
	string lineFromFile;
	int lineNumber=1;
	string doneData="";
	vector <string> doneTokens;
	string newStatus;
	string userLine = T1.getNumber();
	if(userLine=="") {
		return ERROR_DONE;
	}
	//If the line is not empty, each line is checked to find the line number entered by user
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())==lineNumber) {
				doneData = doneData + lineFromFile + "\n";            //doneData stores the original string with status as undone.
				boost::split(doneTokens,lineFromFile,boost::is_any_of("/"));
				doneTokens[10]="done";
			}
		}
		lineNumber++;
	}
	
	//This is used to store the new string with the status as done. It can be accessed by undo if the user wants to unmark this task as done
	//The unmarked done string is stored in original string variable.
	for(i=0;i<doneTokens.size()-1;i++)
		newStatus = newStatus + doneTokens[i] + "/"; 
	if(i==doneTokens.size()-1)
		newStatus = newStatus + doneTokens[i] + "\n";
	//If the line has been found, it is marked as done in the file
	if(doneData!="") {                                 
		S1.updateFileData(doneData,newStatus,fileName,filePath);
		setOriginalDoneTask(doneData);
		setUpdatedDoneTask(newStatus);
		return SUCCESS_DONE;
	} else {
		return ERROR_DONE;
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