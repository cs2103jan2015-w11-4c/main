#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


class Storage {

private:
	string task;
	static vector <string> tasklist;


public:

	bool writeFile(string, string);   //for adding/editing return boolean to Logic
	string readFile (string);		//display items
	//void clearFile();
	void replaceFileData(string,string);
};

#endif;