#ifndef WRONG_H
#define WRONG_H

#include "Command.h"
using namespace std;

class WrongFormat:public Command {	

public:
	WrongFormat();
	string execute(string,string);

};

#endif