#ifndef UNDO_H
#define UNDO_H

#include "Task.h"
#include "Command.h"
#include "Storage.h"
#include "Parser.h"
#include <iostream>

using namespace std;

class Undo: public Command {

private:
	Task T1;
	Storage S1;

public:
	Undo(Task);
	~Undo();
	string execute(string,string); 
	
};

#endif