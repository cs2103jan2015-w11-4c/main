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
	static vector <string> tasklist;

public:

	bool writeFile(Task, string,string);   //for adding/editing return boolean to Logic
	bool checkAdd(Task, string,string);
	string readFile (string,string);		//display items
	bool clearFile(string,string);
	bool checkClear(string,string);
	bool replaceFileData(string,string,string);
	void replaceData (string,string,string,string);
	bool checkDelete(string,string,string);
	int startIndex(string);
	int endIndex(string);
	string extractUserCommand(string,string&);
	bool updateFileData(string,string,string,string);
	void replaceUpdateData(string, string,string,string, string);
	bool checkUpdate(string, string,string,string);
	vector <string> getTaskVector();
	bool writeBackToFile(string,string,string);
	string lowerCase(string);
};

#endif;
