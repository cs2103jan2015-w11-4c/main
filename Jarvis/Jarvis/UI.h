#ifndef UI_H
#define UI_H
#include "Logic.h"
#include <string>
using namespace std;

class UI {

private:
	string _read;
	string _display;
	static const int MAX_BUFFER_SIZE = 255;
	static char buffer[MAX_BUFFER_SIZE];

	static const string MESSAGE_COMMAND;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_DELETED;
	static const string MESSAGE_EDITED;
	static const string MESSAGE_WELCOME;


public:
	static void main(int, char*[]);
	void readLine(string&);
	void getStatus(bool status);
	static void display(string);
};


#endif