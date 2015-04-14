//@author A0118904E
#ifndef DONE_H
#define DONE_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Logic.h"
#include "CommandType.h"
#include "Search.h"
#include <vector>
using namespace std;

class Done:public Command {

private:
	Storage S1;
	Task T1;
	static string updatedDoneTask;
	static string originalDoneTask;

public:
	Done(Task);
	~Done();
	string execute(string,string);
	string executeUndo(string,string);
	int startIndex(string);
	int endIndex(string);
	string extractLineNumber(string);
	string getDoneTask();
	void setOriginalDoneTask(string);
	string getOriginalDoneTask();
	void setUpdatedDoneTask(string);
	string getUpdatedDoneTask();
	bool isValidCommand(string);
};

#endif