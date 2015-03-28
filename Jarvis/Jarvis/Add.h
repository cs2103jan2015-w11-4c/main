#ifndef ADD_H
#define ADD_H

#include "Task.h"
#include "Command.h"
#include "Storage.h"
#include "Delete.h"
#include <iostream>

using namespace std;

class Add: public Command {

private:
	Task T1;
	Storage S1;

public:
	Add(Task);
	~Add();
	string execute(string,string); 
	string executeUndo(string,string);
	
};

#endif