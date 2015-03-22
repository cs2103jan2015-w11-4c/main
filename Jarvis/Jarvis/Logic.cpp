#pragma once
#include "Logic.h"
#include <vector>
#include <fstream>
#include <assert.h>

const string INDENTIFIERS = ".,!? ";

Logic::Logic() {
}

Logic::~Logic() {
}

stack <string> Logic::getStack(){
	return inputStack;
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

	
string Logic::executeCommand(string input, string fileName, string filePath) {
	inputStack.push(input);
	string s="";
	CommandParser P1;
	CommandType C1 = P1.getParserInput(input);
	s = C1.run(fileName,filePath);
	/*command = extractUserCommand(input);
	
	P1.getParsedUserInput(userInput); 
	taskDetails.setDescription(userInput);
	taskDetails.setDate("16");
	taskDetails.setMonth("April");
	taskDetails.setKeywords("May 18 2014");
	taskDetails.setYear("2015");
	
	//try {	
	if(command=="add") {
		/*Add *A1;
		A1=new Add(taskDetails);
		CommandType C1(A1);
		s = C1.run(fileName,filePath);*/
		/*CommandType C1 = P1.getCommand(userInput);
	}
	else if(command=="display") {
		Display *D1;
		D1 = new Display();
		CommandType C1(D1);
		s=C1.run(fileName,filePath);
	}
	else if(command=="delete") {
		taskDetails.setNumber(userInput);
		Delete *Del;
		Del = new Delete(taskDetails);
		CommandType C1(Del);
		s=C1.run(fileName,filePath);
	
	}	
	else if(command=="update") {
		int start = startIndex(userInput);
		int end = endIndex(userInput);
		taskDetails.setUpdated(userInput.substr(end+1)); 
		taskDetails.setNumber(userInput.substr(start,end-start));
		Update *U1;
		U1 = new Update(taskDetails);
		CommandType C1(U1);
		s = C1.run(fileName,filePath);
}
	else if(command=="clear") {
		Clear *C2;
		C2 = new Clear();
		CommandType C1(C2);
		s=C1.run(fileName,filePath);
	}

	else if(command=="exit") {
		
	}

	else if(command=="search") {
		Search *S1;
		S1 = new Search(taskDetails);
		CommandType C1(S1);
		s=C1.run(fileName,filePath);
	}
	else {
		s=" Wrong format of command";
		//throw s;
	}*/
	
//}

//catch(string e) {
	//	cout << "An exception occurred. Exception : Wrong format of command  " << s;
//}
return s;
}