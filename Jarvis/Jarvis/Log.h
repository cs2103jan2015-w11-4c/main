//@author A0111136Y-reused
#include <fstream>
#include <string>
using namespace std;
#pragma once

class Log
{
private:
	ofstream file;

public:

	void clear();
	void log(string);
	void endLog();
};

