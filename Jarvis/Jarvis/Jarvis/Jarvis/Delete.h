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
	int startIndex(string);
	int endIndex(string);
	string extractLineNumber(string);
	string getDeleteTask();
	void setDeleteTask(string);
};

#endif