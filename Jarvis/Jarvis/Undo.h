//@author A0118904E
#ifndef UNDO_H
#define UNDO_H

#include "Task.h"
#include "Command.h"
#include "Storage.h"
#include "Parser.h"
#include "Done.h"
#include <iostream>
#include <stack>

using namespace std;

class Undo: public Command {

private:
	Task T1;
	Storage S1;
	static string command;
	static string inputString;

public:
	Undo(Task);
	Undo();
	~Undo();
	string execute(string,string); 
	bool isCorrectCommand(stack <string>,string&,string&);
	string getUndoCommand();
	string getInputString();
};

#endif
