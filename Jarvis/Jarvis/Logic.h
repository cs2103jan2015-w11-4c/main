//@author A0118904E
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
#include "Search.h"
#include "UI.h"
#include <stack>
#include <boost/algorithm/string.hpp>

using namespace std;


class Logic {

private:
	Task taskDetails;
	string command;
	string userInput;
	stack <string> inputStack;
	bool isDone;

public:
	Logic();
	~Logic();
	string executeCommand(string,stack <string>,string,string);
	string extractUserCommand(string);
	int startIndex(string);
	int endIndex(string);
	stack <string> getStack();
	void setStack(stack <string>);
	string correctNumber(string);
	void setDisplayDone(bool);
	bool getDisplayDone();
	bool isLastCommandDone(stack <string>);
};

#endif
