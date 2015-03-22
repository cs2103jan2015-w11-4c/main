#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Task.h"

using namespace std;


class Storage {

private:
	string task;
	static vector <Task> tasklist;


public:

	bool writeFile(Task, string,string);   //for adding/editing return boolean to Logic
	string readFile (string,string);		//display items
	void clearFile(string,string);
	void replaceFileData(string,string,string);
	int startIndex(string);
	int endIndex(string);
	string extractUserCommand(string,string&);

};

#endif;