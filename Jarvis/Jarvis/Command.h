#ifndef Command_H
#define Command_H

#include <string>
#include <iostream>
#include "Task.h"

using namespace std;



class Command {
public:
	static const string COMMAND_ADD;
	static const string COMMAND_DELETE;
	static const string COMMAND_EXIT;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_UPDATE;

	enum COMMAND_TYPE {
		EXIT, TASKADD, TASKDELETE, TASKUPDATE,TASKDISPLAY
	};

	void taskAdd(Task newTask);
	void taskDelete(int posTask);
	void taskUpdate(int posTask);
	void taskDisplay();


private:
	vector<Task> taskCollection;
	vector<int> searchResults;
	void searchResultsDisplay();
	int pickResult();
	void eraseSearchResults();
	int Command::editTaskPrompt();
	void Command::editTaskExecute(Task editedTask);
};

#endif