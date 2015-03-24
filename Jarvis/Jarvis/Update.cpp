#include "Update.h"
#include <sstream>
#include <iostream>

#include <queue>
using namespace std;


const string INDENTIFIERS = ".,!? ";


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

string Update::execute(string fileName,string filePath) {
	CommandParser P1;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	string lastInput = commandStack.top();
	//Call parser to execute lastInput. It will return a command type object that I will execute to get a input string.
	CommandType C1 = P1.getParserInput(lastInput,commandStack);
	string fileData = C1.run(fileName,filePath);
	bool statusOfUpdate=false;
	string newFileData = "";
	string originalData;
	istringstream file(fileData);
	string lineFromFile;
	int lineNumber=1;
	string userLine = T1.getNumber();
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())==lineNumber) {
				newFileData = T1.getDescription() + "/" + T1.getDate() + "/" + T1.getMonth() + "/" + T1.getYear() + "/";
				originalData = lineFromFile;
				statusOfUpdate=true;
				break;
			}
		 }
		lineNumber++;
	}
	if(!newFileData.empty()) {
		S1.updateFileData(originalData,newFileData,fileName,filePath);
	}
	
	if(statusOfUpdate) {
		return "Updated Successfully\n";
	}
	else {
		return "error in updating task since task specified by line number does not exist\n";
	}
	return newFileData;

}
