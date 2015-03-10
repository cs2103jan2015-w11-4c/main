#pragma once
#include "Logic.h"
#include <vector>

const string INDENTIFIERS = ".,!? ";

Logic::Logic() {
}

Logic::~Logic() {
}

int Logic::startIndex(string input) {
	return input.find_first_not_of(INDENTIFIERS);
}

int Logic::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

string Logic::extractUserCommand(string input) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	userInput = input.substr(end+1); 
	return input.substr(start,end-start);
}

bool Logic::add(string input) {
	return S1.writeFile(taskDetails.getDescription());
}
	
string Logic::executeCommand(string input) {
	command = extractUserCommand(input);
	vector <string> details;
	details = P1.getParsedUserInput(userInput); 
	taskDetails.setDescription(details[0]);
	string s;
	if(command=="add") {
		if(add(taskDetails.getDescription()))
			s= "Added successfully";
		else 
			s= "Error in adding";
	}
	else if(command=="display") {
		vector <string> fileData;
		string fileName;
		fileData = S1.readFile(fileName);
		reverse(fileData.begin(), fileData.end());
		while(!fileData.empty()) {
			s= s + fileData.back() + "\n";
			fileData.pop_back();
		}
	}
	//else if(command=="display") {
		//vector <string> tasks;
		//tasks = readFile();
		//return tasks;
	//}	
	//else if(command=="delete") {

	return s;


}
