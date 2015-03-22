#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

using namespace std;

class Command {

	public:
		virtual string execute(string,string) = 0;

};



#endif