#include "Done.h"
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <stack>
using namespace std;


const string INDENTIFIERS = ".,!? ";
string Done::originalDoneTask;
string Done::updatedDoneTask;


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

string Done::execute(string fileName,string filePath) {
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
	string doneData="";
	vector <string> doneTokens;
	string newStatus;
	string userLine = T1.getNumber();
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
		return "Done";
	}
	
	else {
		return "Error: Please put a correct number. The task could not be marked as done.\n";
	}

}

/*string Done::executeUndo(string fileName,string filePath) {
	string fileData = S1.readFile(fileName,filePath);
	vector <string> data;
	boost::split(data,fileData,boost::is_any_of("\n"));
	data.pop_back();
	S1.replaceFileData(data.back(),fileName,filePath);
	return "The task *" + T1.getUndoString() + "* has been deleted";

}*/

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