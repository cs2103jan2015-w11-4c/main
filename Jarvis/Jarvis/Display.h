#ifndef DISPLAY_H
#define DISPLAY_H

#include "Command.h"
#include "Storage.h"
using namespace std;

class Display:public Command {

private:
	Storage S1;

public:
	Display ();
	~Display();
	string execute(string);

};

#endif