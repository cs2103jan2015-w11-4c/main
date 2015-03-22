#include "UI.h"
#include <iostream>
#include <vector>

using namespace std;

const string UI::MESSAGE_COMMAND = "command: ";
const string UI::MESSAGE_WELCOME = "\n**********************\n* Welcome to Jarvis. *\n**********************\nCommands available: \n( add, delete, display, update, clear, exit)\nData will be written into %s.\n";
const string UI::MESSAGE_BYE = "Goodbye! Press any key to terminate the program . . .";
char UI::buffer[MAX_BUFFER_SIZE];
bool isRunning = true;

int main(int argc, char* argv[]){
	UI::main(argc, argv);
	return 0;
}

void UI::main(int argc, char* argv[]){
	string fileName = argv[1];
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[1]);
	displayLine(buffer);

	while (isRunning){
		cout << MESSAGE_COMMAND;
		string userInput;
		getline(cin, userInput);
		//readLine(userInput);
		Logic temp;
		string userCommand;
		//displayLine(temp.executeCommand(userInput, fileName , filePath));
		userCommand = temp.extractUserCommand(userInput);
		if (userCommand == "exit"){
			isRunning = false;
			displayLine(MESSAGE_BYE);
		}
	}
	return;
}

void UI::displayLine(string text){
	cout << text << endl;
}
