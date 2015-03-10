#include "Storage.h"
#include <vector>
#include <fstream>

using namespace std;

//vector <string> tasklist;

bool Storage::writeFile(string task, string outputfile) {     //if adding/editing function, returns boolean value
	tasklist.push_back(task);
	
	int size;
	size = tasklist.size();

	//start writing into myfile/
	ofstream myfile;                                //write the new sentence into the file
	myfile.open(outputfile.c_str());
	int i=0;

	for (int i=0; i<size; i++) {
	myfile << i+1 << "." << tasklist[i] << endl;      //write specific sentence in. naming like 1.meow   2. woof
	}
	myfile.close();


	if (tasklist[size-1] == task){                  //return status
		return true;
	}
	else {
		return false;
	}
}



//open file then print vector instead??
															
vector <string> Storage::readFile(string outputfile) {				//display all items and return a VECTOR

	/*	 ofstream myfile;									
		myfile.open(outputfile.c_str());
		int i=0;

		while (tasklist[i]!="") {					   	  
			myfile<<i+1<<". "<<tasklist[i] <<endl;         
			++i;
		}
		myfile.close();
	*/

	return tasklist;
}



//simple delete function, haven't save deleted line in myfile
bool Storage::deleteTask(int number) {							//delete requested number of string
	int sizebeforedelete = tasklist.size();
	tasklist.erase(tasklist.begin() + (number-1));

	if (tasklist.size() == (sizebeforedelete - 1)) {                  //return status
		return true;
	}
	else {
		return false;
	}
	}



/* bool Storage::returnStatusAdded(vector <string> tasklist) {   //if adding/delete succeed return with boolean 0 or 1
	int size;
	size = tasklistsize();
	if (tasklist[size-1] == task){
		return true;
	}
	else {
		return false;
	}
}
*/