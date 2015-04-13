#include "redo.h"
#include <boost/algorithm/string.hpp>

const string ERROR_WRONG_COMMAND = "Error: Redo is supported only for ADD,DELETE,UPDATE,CLEAR,DONE\nCannot undo SEARCH, DISPLAY OR HELP commands";
const string DISPLAY_COMMAND = "display"; 
const string ERROR_REDO = "Error: Incorrect format of command *redo*\n Enter *redo* to revert changes made by the latest *undo* command";
const string ERROR_NO_TASK = "Error: No undo had been executed to REDO.\nREDO can only be performed after an UNDO command has been executed.";
const string UNDO_DONE = " The task is no longer marked as *done*";
const string UNDO_COMMAND = "undo";

Redo::Redo(Task taskObject,Undo undoObject) {
	T1 = taskObject;
	U1 = undoObject;
}

Redo::~Redo() {

}

bool Redo::isCorrectCommand(stack <string> inputCommands, string& commandToRedo , string& userInput) {
	string topInput;
	string topCommand;
	CommandParser P1;
	while(!inputCommands.empty()) {
		topInput = inputCommands.top();
		topCommand = P1.extractUserCommand(topInput); 
		if(topCommand!=UNDO_COMMAND || topCommand!=DISPLAY_COMMAND) {
			return false;
		}
		else if(topCommand==DISPLAY_COMMAND) {
			inputCommands.pop();
		}
		else {
			commandToRedo = U1.getUndoCommand() ;
			userInput = U1.getInputString();
			return true;
		}
	}
	return false;
}

string Redo::execute(string fileName, string filePath) {
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
		return ERROR_REDO;
	}
	
	bool redoCommand = isCorrectCommand(commandStack,lastCommand, userInput);
	if(redoCommand) {
		string input = lastCommand + " " + userInput;
		return L1.executeCommand(input,commandStack,fileName,filePath);
	}
	else {
		return ERROR_WRONG_COMMAND;
	}
}
