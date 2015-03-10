#ifndef UI_H
#define UI_H

#include <string>
#include "Logic.h"
using namespace std;

class UI {

private:
	static const int MAX_BUFFER_SIZE = 255;
	static char buffer[MAX_BUFFER_SIZE];	
	static const string MESSAGE_COMMAND;
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_BYE;

public:

	static void main(int, char*[]);
	//static void readLine(string);
	static void displayLine(string);
	void getStatus(bool status);
	
};

#endif