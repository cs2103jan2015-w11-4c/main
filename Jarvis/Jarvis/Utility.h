#ifndef UTILITY_H
#define UTILITY_H

#include "Command.h"
#include <string>

using namespace std;

class Utility {
public:
	static bool stringToBool(string s);
	static string boolToString(bool b);
	static Command::COMMAND_TYPE stringToCOMMAND_TYPE(string command);
	static string COMMAND_TYPEToString(Command::COMMAND_TYPE cmd);
	
private:
	static bool isExit(string command);
	static bool isAdd(string command);
	static bool isDelete(string command);
	static bool isUpdate(string command);
	static bool isDisplay(string command);
	
	static const int SAME;
};

#endif