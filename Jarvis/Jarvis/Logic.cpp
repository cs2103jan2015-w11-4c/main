#pragma once
#include "Logic.h"
#include <vector>
#include <fstream>
#include <assert.h>

const string INDENTIFIERS = ".,!? ";
vector <pair <int, int>>::iterator iter;

Logic::Logic() {
	isDone=false;
}


Logic::~Logic() {
}

stack <string> Logic::getStack() {
	return inputStack;
}

void Logic::setStack(stack <string> input) {
	inputStack=input;
}

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

int Logic::startIndex(string input) {
	
	return input.find_first_not_of(INDENTIFIERS);
}

int Logic::endIndex(string input) {
	return input.find_first_of(INDENTIFIERS);
}

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


string Logic::executeCommand(string input,stack <string> userStack, string fileName, string filePath) {
	inputStack=userStack;
	string s;
	CommandParser P1;
	CommandType C1 = P1.getParserInput(input,getStack());
	s = C1.run(fileName,filePath);
	return s;
}

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

bool Logic::getDisplayDone() {
	return isDone;
}