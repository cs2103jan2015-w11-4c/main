#ifndef LOGIC_H
#define LOGIC_H

#include "Task.h"
//#include "Parser.h"
#include "Storage.h"
//#include <boost/algorithm/string/trim.hpp>

using namespace std;
//using namespace boost::algorithm;

class Logic {

private:
	Task taskDetails;
	//Parser P1;
	Storage S1;
	string command;
	string userInput;

public:
	Logic();
	~Logic();
	bool executeCommand(string);
	string extractUserCommand(string);
	int startIndex(string);
	int endIndex(string);

};

#endif
