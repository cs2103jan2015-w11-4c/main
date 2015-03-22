#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <string>
#include <sstream>
#include "Command.h"
#include "Task.h"
#include "Storage.h"
#include <vector>
using namespace std;

class Search: public Command {

private:
	Task T1;
	Storage S1;
public:
	Search();
	Search(Task);
	~Search();
	string execute(string,string);
	string executeSearch(string,string);
	string changeToLowerCase(string);
};

#endif;