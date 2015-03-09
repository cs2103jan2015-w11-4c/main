
#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Storage {

private:
	string task;
	vector <string> tasklist;


public:
	bool writeFile(string, vector <string> tasklist);   //for adding/editing return boolean to Logic
	vector <string> readFile (string);		//display items
	//string deleteTask(string);
	//bool returnStatus();        //if adding/delete succeed return with boolean 0 or 1

};

#endif