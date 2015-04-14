//@author A0118904E
#pragma once
#include "Logic.h"
#include <vector>
#include <assert.h>

vector <pair <int, int>>::iterator iter;

Logic::Logic() {
	isDone=false;  
}

Logic::~Logic() {
}

//This is a universal stack that stores all the inputs by the user since the application had opened
stack <string> Logic::getStack() { 
	return inputStack;
}

void Logic::setStack(stack <string> input) {
	inputStack=input;
}

//This tells us whether the recent task executed was "display done" to enable deleting a done task.
bool Logic::isLastCommandDone(stack <string> input) {
	string userCommand;
	if(!input.empty()) {
		userCommand = input.top();
		command = extractUserCommand(userCommand);
		if(command=="display" && userInput=="done") {
			return true;
		} else {
			return false;
		}
	}

}

//This extracts the command type from the task input
//Simultaneously it trims the spaces in the input
string Logic::extractUserCommand(string input) {
	vector <string> tokensBeforeTrim;
	boost::split(tokensBeforeTrim,input,boost::is_any_of(" "));
	vector <string> tokens;
	for(int i=0;i<tokensBeforeTrim.size();i++) {
		if(tokensBeforeTrim[i]!=" ") {
			tokens.push_back(tokensBeforeTrim[i]);
		}
	}
	string taskString;
	int i;
	for(i=1;i<tokens.size()-1;i++) {
		taskString = taskString + tokens[i] + " ";
	}
	if(i==tokens.size()-1) {
		taskString = taskString + tokens[i];
	}
	userInput=taskString;

	return tokens[0];
}

//This is the main function that executes the command and returns a status message to the user
string Logic::executeCommand(string input,stack <string> userStack, string fileName, string filePath) {
	inputStack=userStack;
	string status;
	CommandParser P1;
	CommandType C1 = P1.getParserInput(input,getStack());
	status = C1.run(fileName,filePath);
	return status;
}

//This is to facilitate the different numbering the user observes on the screen and the numbering in the storage file.
//Example, the line 1 on the screen (command window) may not be task 1 in the file, depending on the category of display( by month)
//If the number input is invalid, it returns a blank string
string Logic::correctNumber(string no) {
	string number="";
	for (iter = UI::indexPair.begin(); iter != UI::indexPair.end(); iter++){
		if (atoi(no.c_str()) == iter->first) {
			number = to_string(iter->second);
		}
	}
return number;
}

void Logic::setDisplayDone(bool value) {
	isDone = value;
}

//Tells us if a done task has been executed
bool Logic::getDisplayDone() {
	return isDone;
}
