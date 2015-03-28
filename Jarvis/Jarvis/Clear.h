#ifndef CLEAR_H
#define CLEAR_H

#include "Command.h"
#include "Storage.h"
using namespace std;

class Clear:public Command {

private:
	Storage S1;
	static string originalData;

public:
	Clear();
	~Clear();
	string execute(string,string);
	void setData(string);
	string getData();
};

#endif