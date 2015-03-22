#ifndef DISPLAY_H
#define DISPLAY_H

#include "Command.h"
#include "Storage.h"
#include "Task.h"
#include "Search.h"
using namespace std;

class Display:public Command {

private:
	Storage S1;
	Task T1;

public:
	Display();
	Display(Task);
	~Display();
	string execute(string,string);

};

#endif