#include "Command.h"
#include "Parser.h"
#include "Task.h"
#include <stdio.h>

const string Command::COMMAND_ADD = "add";
const string Command::COMMAND_DELETE = "delete";
const string Command::COMMAND_EXIT = "exit";
const string Command::COMMAND_UPDATE = "update";
 
void Command::taskAdd(Task newTask) {
	taskCollection.push_back(newTask);
}

void Command::taskDelete(int posTask) {
	taskCollection.erase(taskCollection.begin() + posTask);
	eraseSearchResults();
}  

void Command::taskDisplay() {
	for(unsigned i=0; i<taskCollection.size(); i++) {
		Task resultTask = taskCollection.at(i);
		string resultName = resultTask.getName();

		cout << i << '. ' << resultName << endl;
	}
}


void Command::taskUpdate(int posTask) {
	int i = searchResults.at(posTask);

	eraseSearchResults();
}
                                                                                


