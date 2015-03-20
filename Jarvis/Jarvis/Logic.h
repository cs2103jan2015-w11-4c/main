#ifndef LOGIC_H
#define LOGIC_H

#include "Task.h"
#include "Parser.h"
#include "Storage.h"
#include "CommandType.h"
#include "Add.h"
#include "Display.h"
#include "Delete.h"
#include "Update.h"
#include "Clear.h"
//#include <boost/algorithm/string/trim.hpp>

using namespace std;
//using namespace boost::algorithm;

class Logic {

private:
	Task taskDetails;
	CommandParser P1;
	string command;
	string userInput;

public:
	Logic();
	~Logic();
	string executeCommand(string,string);
	string extractUserCommand(string);
	int startIndex(string);
	int endIndex(string);

};

#endif
