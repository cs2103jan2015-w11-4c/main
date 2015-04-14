//@author A0118904E
#include "Delete.h"
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <stack>
using namespace std;

string Delete::deleteTask;
const string DISPLAY_COMMAND = "display";
const string ERROR_PREVIOUS_COMMAND = "Error: Please view your task list using the *DISPLAY* command before deleting a task";
const string ERROR_DELETE = "Error: Please enter *DELETE* followed by the correct number of the task to be deleted.\n";
const string SUCCESS_DELETE = "Deleted task successfully\n";

Delete::Delete(Task TaskAttributes) {
	T1=TaskAttributes;
}

Delete::~Delete() {

}

//A user can only delete a task after a display command has been entered
//This allows deleting by category. 
bool Delete::isValidCommand(string input) {   
	if(input==DISPLAY_COMMAND) {
		return true;
	} else {
		return false;
	}
}


string Delete::execute(string fileName,string filePath) {
	CommandParser P1;
	string s;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	//The command stack stores all the inputs entered by the user since the program has started
	//If the stack is empty after removing this "delete" command, the user is not allowed to delete.
	if(commandStack.empty()) {
		return ERROR_PREVIOUS_COMMAND;
	}
	string lastInput = commandStack.top();
	CommandType C1 = P1.getParserInput(lastInput,commandStack);
	string command = P1.getCommand();
	//The user can only delete after a display command
	if(!isValidCommand(command)) {
		return ERROR_PREVIOUS_COMMAND;
	}
	//retrieves the input specified by the last display command
	//If the user has entered display march, all the tasks in march are called so that he can delete from this list
	string input = C1.run(fileName,filePath);
	istringstream file(input);
	string lineFromFile;
	int lineNumber=1;
	string deletedData="";
	string userLine = T1.getNumber();
	//If the line is not empty, each line is checked to find the line number entered by user. This is then deleted.
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())==lineNumber) {
				deletedData = deletedData + lineFromFile + "\n";
			}
			
	}
		lineNumber++;
	}
	if(deletedData!="") {            //If the line has been found, it is removed from the file
		S1.replaceFileData(deletedData,fileName,filePath);
		setDeleteTask(deletedData);
		return SUCCESS_DELETE;
	} else {
		return ERROR_DELETE;
	}
}

//Used to delete the last command added incase user wants to undo an add
string Delete::executeUndo(string fileName,string filePath) {
	string fileData = S1.readFile(fileName,filePath);
	vector <string> data;
	boost::split(data,fileData,boost::is_any_of("\n"));
	data.pop_back();
	S1.replaceFileData(data.back(),fileName,filePath);
	return "The task *" + T1.getUndoString() + "* has been deleted";
}

string Delete::getDeleteTask() {
	return deleteTask;
}
void Delete::setDeleteTask(string task) {
	deleteTask=task;
}