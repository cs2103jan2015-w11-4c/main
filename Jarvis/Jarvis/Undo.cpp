#include "Undo.h"
#include <boost/algorithm/string.hpp>

const string ERROR_DISPLAY = "Error: Undo is supported only for ADD,DELETE,UPDATE,CLEAR\nCannot undo";
const string DISPLAY_COMMAND = "display"; 
const string ADD_COMMAND = "add";
const string DELETE_COMMAND = "delete";
const string UPDATE_COMMAND = "update";
const string CLEAR_COMMAND = "clear";
const string ERROR_UNDO = "Error: Incorrect format of command *undo*\n Enter *undo last* to undo the last command";
const string UNDO_KEYWORD = "last";

Undo::Undo(Task taskObject) {
	T1 = taskObject;
}

Undo::~Undo() {

}

string Undo::execute(string fileName, string filePath) {
	CommandParser P1;
	if(T1.getKeywords()==UNDO_KEYWORD) {
		stack <string> commandStack = T1.getStack();
		commandStack.pop();
		string m;
		string lastInput = commandStack.top();
		string lastCommand = P1.extractUserCommand(lastInput);
		string userInput = P1.getUserInput();
		string userFeedback;
		if(lastCommand==DISPLAY_COMMAND) {
			return ERROR_DISPLAY;
		}
		else if(lastCommand==ADD_COMMAND) {
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
			return "The update to the task has been reverted";
		}
		else if(lastCommand==CLEAR_COMMAND) {
			Clear C1(T1);
			bool status = S1.writeBackToFile(C1.getData(),fileName,filePath);
			return "The contents of the file have been restored";
		}

	}

	else {
		return ERROR_UNDO;

	}
}
