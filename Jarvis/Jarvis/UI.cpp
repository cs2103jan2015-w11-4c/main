#include "UI.h"
#include <iostream>
#include <vector>

using namespace std;

const string UI::MESSAGE_COMMAND = "command: ";
const string UI::MESSAGE_WELCOME = "Welcome to Jarvis. %s is ready.";

bool isRunning = true;

int main(int argc, char* argv[]){
	UI::main(argc, argv);
	return 0;
}

void UI::main(int argc, char* argv[]){
	setFileName(argv[1]);
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[1]);
	displayLine(buffer);

	while (isRunning){
		cout << MESSAGE_COMMAND;
		string userInput;
		readLine(userInput);
		Logic temp;
		string userCommand;
		displayLine(temp.executeCommand(userInput));
		userCommand = temp.extractUserCommand(userInput);
		if (userCommand == "exit"){
			isRunning = false;
		}
	}
	return;
}

string UI::getFileName(){
	return _fileName;
}

void UI::setFileName(string fileName){
	_fileName = fileName;
	return;
}

void UI::displayLine(string text){
	cout << text << endl;
}

void UI::readLine(string userInput){
	getline(cin, userInput);
	return;
}