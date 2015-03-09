#include "Logic.h"

using namespace std;


const string INDENTIFIERS = ".,!? ";


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


bool Logic::executeCommand(string input) {
	command = extractUserCommand(input);

}	