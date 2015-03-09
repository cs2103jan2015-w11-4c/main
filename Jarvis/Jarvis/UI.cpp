#include "UI.h"
#include <iostream>
#include <vector>

using namespace std;

const string UI::MESSAGE_COMMAND = "command: ";
const string UI::MESSAGE_ADDED = "Task has been added.";
const string UI::MESSAGE_DELETED = "Task has been deleted.";
const string UI::MESSAGE_EDITED = "Task has been edited.";
const string UI::MESSAGE_WELCOME = "Welcome to Jarvis. %s is ready.";

bool isRunning = true;

int main(int argc, char* argv[]){
	UI::main(argc, argv);
	return 0;
}

void UI::main(int argc, char* argv[]){
	string fileName = argv[1];
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[1]);
	display(buffer);

	while (isRunning){
		cout << MESSAGE_COMMAND;
		string userInput;
		//readLine(UserInput)
	}

}
void UI::display(string text){
	cout << text << endl;
}

void UI::readLine(string UserInput){
	return;
}

