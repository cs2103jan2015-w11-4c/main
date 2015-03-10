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

bool Logic::add(string input,string fileName) {
	//Storage S1;
	return S1.writeFile(taskDetails.getDescription(),fileName);
}
	
string Logic::executeCommand(string input, string fileName) {
	command = extractUserCommand(input);
	vector <string> details;
	//CommandParser P1;
	//details = P1.getParsedUserInput(userInput); 
	taskDetails.setDescription(input);
	string s;
	if(command=="add") {
		if(add(taskDetails.getDescription(),fileName))
			s= "Added successfully";
		else 
			s= "Error in adding";
	}
	else if(command=="display") {
		vector <string> fileData;
		///Storage S1;
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
