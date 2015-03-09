#include "Storage.h"
#include <vector>

using namespace std;

vector <string> tasklist;

string Storage::writeFile(string task) {     //if add function, push task into vector, 
	tasklist.push_back(task);

}
