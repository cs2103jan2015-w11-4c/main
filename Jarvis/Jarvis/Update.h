#ifndef UPDATE_H
#define UPDATE_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Parser.h"
#include <iostream>
using namespace std;

class Update:public Command {

private:
	Storage S1;
	Task T1;
	static string originalTask;
	static string updatedTask;

public:
	Update(Task);
	~Update();
	string execute(string,string);
	int startIndex(string);
	int endIndex(string);
	string extractLineNumber(string);
	void setOriginalTask(string);
	string getOriginalTask();
	void setUpdatedTask(string);
	string getUpdatedTask();
	string lowerCase(string);
};

#endif
