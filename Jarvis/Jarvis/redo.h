#ifndef REDO_H
#define REDO_H

#include "Logic.h"
#include "Task.h"
#include "Undo.h"

#include "Command.h"
#include <iostream>
#include <stack>

using namespace std;

class Redo:public Command {

private:
	Task T1;
	Undo U1;
	Logic L1;

public:
	Redo(Task,Undo);
	~Redo();
	string execute(string,string); 
	bool isCorrectCommand(stack <string>,string&,string&);
	
};

#endif
