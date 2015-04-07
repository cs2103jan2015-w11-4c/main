#include "Delete.h"
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <stack>
using namespace std;


const string INDENTIFIERS = ".,!? ";
string Delete::deleteTask;


Delete::Delete(Task TaskAttributes) {
	T1=TaskAttributes;
}

Delete::~Delete() {

}

int Delete::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int Delete::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string Delete::extractLineNumber(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	return input.substr(end+2); 
}

string Delete::execute(string fileName,string filePath) {
	CommandParser P1;
	string s;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	string lastInput = commandStack.top();
	//Call parser to execute lastInput. It will return a command type object that I will execute to get a input string.
	CommandType C1 = P1.getParserInput(lastInput,commandStack);
	string input = C1.run(fileName,filePath);
	istringstream file(input);
	string lineFromFile;
	int lineNumber=1;
	string deletedData="";
	string userLine = T1.getNumber();
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())==lineNumber) {
				deletedData = deletedData + lineFromFile + "\n";
			}
			
	}
		lineNumber++;
	}
	
	if(deletedData!="") {
		S1.replaceFileData(deletedData,fileName,filePath);
		setDeleteTask(deletedData);
		return "Deleted successfully\n";
	}
	
	else {
		return "Error: Could not delete task since task does not exist\n";
	}

}

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