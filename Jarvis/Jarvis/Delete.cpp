#include "Delete.h"
#include <sstream>
#include <iostream>

#include <queue>
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

string Delete::execute(string fileName) {

	bool statusOfDelete=false;
	string fileData = S1.readFile(fileName);
	string newFileData = "";
	istringstream file(fileData);
	string lineFromFile;
	int lineNumber=1;
	string userLine = T1.getNumber();
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			if(atoi(userLine.c_str())!=lineNumber) {
				newFileData = newFileData + extractLineNumber(lineFromFile) + "\n";
		}
		else { 
			statusOfDelete=true;
		}
		lineNumber++;
		}
	}
	
	if(!newFileData.empty()) {
		S1.replaceFileData(newFileData,fileName);
	}
	
	if(statusOfDelete) {
		return "Deleted successfully\n";
	}
	else {
		return "error in deletion since task does not exist\n";
	}


}