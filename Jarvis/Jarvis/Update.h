#ifndef UPDATE_H
#define UPDATE_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
using namespace std;

class Update:public Command {

private:
	Storage S1;
	Task T1;

public:
	Update(Task);
	~Update();
	string execute(string,string);
	int startIndex(string);
	int endIndex(string);
	string extractLineNumber(string);
};

#endif