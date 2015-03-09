
#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

using namespace std;


class Storage {

private:
	string task;
	vector <string> tasklist;


public:
	bool writeFile(string);   //for adding/editing return boolean to Logic
	//string deleteTask(string);
	//string readFile(string);        //display items
	//bool returnStatus();        //if adding/delete succeed return with boolean 0 or 1

};

#endif