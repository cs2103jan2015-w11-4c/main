#ifndef STORAGE_H
#define STORAGE_H

#include <string>

using namespace std;


class Storage {

private:
	string task;
	vector <string> tasklist;


public:
	bool writeFile(string, vector <string> tasklist);   //for adding/editing will return a boolean
	string deleteTask(string);
	string readFile(string);        //display items
	//bool returnStatus();        //if adding/delete succeed return with boolean 0 or 1

};

#endif