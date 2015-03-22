#ifndef DELETE_H
#define DELETE_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Logic.h"
#include "CommandType.h"
using namespace std;

class Delete:public Command {

private:
	Storage S1;
	Task T1;

public:
	Delete(Task);
	~Delete();
	string execute(string,string);
	int startIndex(string);
	int endIndex(string);
	string extractLineNumber(string);
};

#endif