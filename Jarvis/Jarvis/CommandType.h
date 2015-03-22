#ifndef CommandType_H
#define CommandType_H

#include "Command.h"
using namespace std;

class CommandType {

private:

	Command* C1;

public:

	CommandType(Command*);
	~CommandType();
	string run(string);
};

#endif