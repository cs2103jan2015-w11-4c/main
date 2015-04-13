#include "Undo.h"
#include <boost/algorithm/string.hpp>

const string ERROR_WRONG_COMMAND = "Error: Undo is supported only for ADD,DELETE,UPDATE,CLEAR,DONE\nCannot undo SEARCH, DISPLAY OR HELP commands";
const string DISPLAY_COMMAND = "display"; 
const string ADD_COMMAND = "add";
const string DELETE_COMMAND = "delete";
const string UPDATE_COMMAND = "update";
const string CLEAR_COMMAND = "clear";
const string DONE_COMMAND = "done";
const string USER_HELP_COMMAND = "help";
const string SEARCH_COMMAND = "search";
const string ERROR_UNDO = "Error: Incorrect format of command *undo*\n Enter *undo* to undo the last command";
const string ERROR_NO_TASK = "Error: Undo can only be performed after ADD,DELETE,UPDATE,DONE OR CLEAR. Enter a command to Undo";
const string UNDO_DONE = " The task is no longer marked as *done*";

string Undo::command;
string Undo::inputString;

Undo::Undo(Task taskObject) {
	T1 = taskObject;
	
}

Undo::Undo() {
	command="";
	inputString="";
}

Undo::~Undo() {

}

bool Undo::isCorrectCommand(stack <string> inputCommands, string& commandToUndo , string& userInput) {
	string topInput;
	string topCommand;
	CommandParser P1;
	while(!inputCommands.empty()) {
		topInput = inputCommands.top();
		topCommand = P1.extractUserCommand(topInput); 
		if(topCommand==USER_HELP_COMMAND || topCommand==SEARCH_COMMAND) {
			return false;
		}
		else if(topCommand==DISPLAY_COMMAND) {
			inputCommands.pop();
		}
		else {
			commandToUndo = topCommand;
			command = commandToUndo;
			userInput = P1.getUserInput();
			inputString = userInput;
			return true;
		}
	}
	return false;

}

string Undo::execute(string fileName, string filePath) {
	CommandParser P1;
	string lastCommand;
	string userFeedback;
	string userInput;
	stack <string> commandStack = T1.getStack();
	commandStack.pop();
	if(commandStack.empty()) {
		return ERROR_NO_TASK;
	}
	if(!T1.getBlankString()) {
		return ERROR_UNDO;
	}
	bool undoCommand = isCorrectCommand(commandStack,lastCommand, userInput);
	if(undoCommand) {
		if(lastCommand==ADD_COMMAND) {
			T1.setUndoString(userInput);
			Delete D1(T1);
			userFeedback = D1.executeUndo(fileName,filePath);
			return userFeedback;
		}
		else if(lastCommand==DELETE_COMMAND) {
			RecurringTask R1;
			Add A1(T1,R1);
			userFeedback = A1.executeUndo(fileName,filePath);
			return userFeedback;

		}
		else if(lastCommand==UPDATE_COMMAND) {
			Update U1(T1);
			boost::trim(userInput);
			Task T1 = P1.parserUpdate(userInput);
			S1.updateFileData(U1.getUpdatedTask(),U1.getOriginalTask(),fileName,filePath); 
			return "The update to the task has been reverted\n" ;
		}
		else if(lastCommand==CLEAR_COMMAND) {
			Clear C1(T1);
			bool status = S1.writeBackToFile(C1.getData(),fileName,filePath);
			return "The contents of the file have been restored";
		}
		else {
			Task T1;
			Done doneObject(T1);
			S1.updateFileData(doneObject.getUpdatedDoneTask(),doneObject.getOriginalDoneTask(),fileName,filePath);
			return UNDO_DONE;
		}
	}
	else {
		return ERROR_WRONG_COMMAND;
	}
}

string Undo::getUndoCommand() {
	return command;
}

string Undo::getInputString() {
	return inputString;
}
