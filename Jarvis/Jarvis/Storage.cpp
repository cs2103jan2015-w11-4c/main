#include "Storage.h"
#include <vector>

using namespace std;

vector <string> tasklist;

bool Storage::writeFile(string task) {     //if adding/editing function, returns boolean value
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

/*string deleteTask(string) {   //delete requested string
}
*/

/*string readFile(string) {		//display all items
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
