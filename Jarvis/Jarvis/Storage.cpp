#include "Storage.h"
#include "Assert.h"
#include <vector>
#include <fstream>

using namespace std;

vector <string> Storage::tasklist;

bool Storage::writeFile(string task, string outputfile) {     //if adding/editing function, returns boolean value
	
	tasklist.push_back(task);
	
	int size;
	size = tasklist.size();
	assert(size >= 1);

	for (int i = 0; i < size; i++)
	{
		cout << tasklist[i] << endl;
	}
	//Asert(i!=2);
	//start writing into myfile/
	ofstream myfile;                                //write the new sentence into the file
	myfile.open(outputfile.c_str(),ios::app);
	myfile << task << endl;

	//int i=0;
	//for (int i=0; i<size; i++) {
	//myfile << i+1 << "." << tasklist[i] << endl;      //write specific sentence in. naming like 1.meow   2. woof
	//}
	myfile.close();


	if (tasklist[size-1] == task){                  //return status
		return true;
	}
	else {
		return false;
	}
}




//open file then print vector instead??
															
//vector <string> 
string Storage::readFile(string outputfile) {				//display all items and return a VECTOR
	ifstream readfile(outputfile);
	string fileContent="";
	//If the file is empty
	if(readfile.peek()==std::ifstream::traits_type::eof()) {
		cout << outputfile << " is empty" << endl << endl;
	}

	else {
		int lineNumber=1;
		while(!readfile.eof()) {
			string line;
			getline(readfile,line);
			if(!line.empty()) {
				fileContent = fileContent + to_string(lineNumber) + ". " + line + "\n";
				lineNumber++;
			}
		}
	}
	readfile.close();
	return fileContent;

}
	/*	 ofstream myfile;									
		myfile.open(outputfile.c_str());
		int i=0;

		while (tasklist[i]!="") {					   	  
			myfile<<i+1<<". "<<tasklist[i] <<endl;         
			++i;
		}
		myfile.close();
	*/

	//return tasklist;






/*void Storage::clearFile() {
	tasklist.clear();
	assert (tasklist.size() == 0);
}
*/

	/*int sizebeforedelete = tasklist.size();
	tasklist.erase(tasklist.begin() + (number-1));

	if (tasklist.size() == (sizebeforedelete - 1)) {                  //return status
		return true;
	}
	else {
		return false;
	}
	}
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

void Storage::replaceFileData(string newFileData,string fileName) {
	//tasklist = newFileData;
	ofstream writeFile;
	writeFile.open(fileName,ios::trunc);
	istringstream file(newFileData);
	string lineFromFile;
	while(getline(file,lineFromFile)) {
		if(!lineFromFile.empty()) {
			writeFile << lineFromFile << endl;
		}
	}
	writeFile.close();
}