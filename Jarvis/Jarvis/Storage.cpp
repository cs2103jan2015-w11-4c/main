#include "Storage.h"
#include <vector>
#include <fstream>

using namespace std;

vector <string> tasklist;

bool Storage::writeFile(string task, string outputfile) {     //if adding/editing function, returns boolean value
	tasklist.push_back(task);
	
	int size;
	size = tasklist.size();

	//start writing into myfile
	ofstream myfile;                                //write the new sentence into the file
	myfile.open(outputfile.c_str());
	int i=0;

	myfile<<size<<"."<<tasklist[size-1]<<endl;      //write specific sentence in. naming like 1.meow   2. woof

	myfile.close();


	if (tasklist[size-1] == task){                  //return status
		return true;
	}
	else {
		return false;
	}
}



//open file then print vector instead??
															
vector <string> Storage::readFile (string outputfile) {				//display all items and return a VECTOR
		 ofstream myfile;									
		myfile.open(outputfile.c_str());
		int i=0;

		while (tasklist[i]!="") {					   	  
			myfile<<i+1<<". "<<tasklist[i] <<endl;         
			++i;
		}
		myfile.close();

	return tasklist;
}



//eg. delete meow. logic will call .deleteTask, 
//inside my deletetask I need to call search function and return all sentences with meow inside. return vector of lines. 
//user will choose one of them, I will delete vector line.

/*string deleteTask(string) {   //delete requested string
	}
//my own delete function, i will call search if search == 1, delete it straightaway. If got 2 vectors, send back to user
*/


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