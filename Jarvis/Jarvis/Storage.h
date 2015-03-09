#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

//ask about so if logic has its own function, if ("add) will .writefile in storage
//if delete, will call read file, then call delete again. I just write functions?

using namespace std;


class Storage {

private:
	string task;
	vector <string> tasklist;


public:
	string writeFile(string);   //for adding items in, if edit, will .writefile(to push new items into vector)
	//string Delete()
	string readFile(string);        //display items
	bool returnStatus();        //if adding/delete succeed return with boolean 0 or 1

};

#endif