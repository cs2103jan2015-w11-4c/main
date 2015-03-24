#include "Delete.h"
#include <sstream>
#include <iostream>

#include <stack>
using namespace std;


const string INDENTIFIERS = ".,!? ";


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
	/*Logic L1;
	stack <string> commandQueue = L1.getStack();
	commandQueue.pop();
	string lastInput = commandQueue.top();*/
	//Call parser to execute lastInput. It will return a command type object that I will execute to get a input string.
	/*Display *D1;
	D1 = new Display();
	CommandType C1(D1);
	string input = C1.run(fileName,filePath);*/
	string input = S1.readFile(fileName,filePath);
	istringstream file(input);
	string lineFromFile;
	int lineNumber=1;
	string newData="";
	string userLine = T1.getNumber();
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())!=lineNumber) {
				newData = newData + lineFromFile + "\n";
			}
			
	}
		lineNumber++;
	}
	
	if(newData!="") {
		S1.replaceFileData(newData,fileName,filePath);
		return "Deleted successfully\n";
	}
	
	else {
		return "error in deletion since task does not exist\n";
	}

}