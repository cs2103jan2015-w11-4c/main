#ifndef UI_H
#define UI_H

#include <string>
#include "Logic.h"
using namespace std;

class UI {

private:
	static string _fileName;
	static const int MAX_BUFFER_SIZE = 255;
	static char buffer[MAX_BUFFER_SIZE];

	static const string MESSAGE_COMMAND;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_DELETED;
	static const string MESSAGE_EDITED;
	static const string MESSAGE_WELCOME;


public:
	static void main(int, char*[]);
	static void readLine(string);
	static void displayLine(string);
	void getStatus(bool status);
	static void setFileName(string fileName);
	string getFileName();
	
};

#endif