#include "Storage.h"
#include <vector>
#include <fstream>

using namespace std;

vector <string> tasklist;

bool Storage::writeFile(string task, vector <string> tasklist) {     //if adding/editing function, returns boolean value
	tasklist.push_back(task);
	
	int size;
	size = tasklist.size();
	if (tasklist[size-1] == task){
		return true;
	}
	else {
		return false;
	}

}

															//display all items and return a VECTOR
vector <string> readFile (string outputfile) {				//user defined i wanna paste my vector inside text file
		ofstream myfile;									//entire step is to write into text file
		myfile.open(outputfile.c_str());
		int i=0;

		while (tasklist[i]!="") {					   	    //while theres something to write/not empty
			myfile<<i+1<<". "<<tasklist[i] <<endl;          //naming like 1.meow  2. woof
			++i;
		}
		myfile.close();

	return tasklist;
}



/*string deleteTask(string) {   //delete requested string
}
*/



/* bool Storage::returnStatusAdded(vector <string> tasklist) {   //if adding/delete succeed return with boolean 0 or 1
	int size;
	size = tasklist.size();
	if (tasklist[size-1] == task){
		return true;
	}
	else {
		return false;
	}
}
*/
