//@author A0118904E
#ifndef DELETE_H
#define DELETE_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Logic.h"
#include "CommandType.h"
#include "Search.h"
#include <vector>
using namespace std;

class Delete:public Command {

private:
	Storage S1;
	Task T1;
	static string deleteTask;

public:
	Delete(Task);
	~Delete();
	string execute(string,string);
	string executeUndo(string,string);
	string getDeleteTask();
	void setDeleteTask(string);
	bool isValidCommand(string);
};

#endif