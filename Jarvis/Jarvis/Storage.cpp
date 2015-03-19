#include "Storage.h"
#include "Assert.h"
#include <vector>
#include <fstream>
#include <queue>

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




//simple delete function, haven't save deleted line in myfile
bool Storage::deleteTask(string userInput,string fileName) {							//delete requested number of string
	ifstream readfile(fileName);
	queue <string> fileData;  
	string lineFromFile;
	bool deleted=false;
	int lineNumber=1;
	while(!readfile.eof()) {
 		getline(readfile,lineFromFile);	
		if(!lineFromFile.empty()) {
		if(atoi(userInput.c_str())!=lineNumber) {
			fileData.push(lineFromFile);
		}
		else { 
			deleted=true;
		}
		lineNumber++;
	}
	}
	readfile.close();
	ofstream writefile;
	writefile.open(fileName,ios::trunc);
	while(!fileData.empty()) {
		writefile << fileData.front() <<endl;
		fileData.pop();
	}

	return deleted;
}
	

bool Storage::updateFile(string fileName, string lineNumber, string updatedString)	{
	ifstream readfile(fileName);
	queue <string> fileData;  
	string lineFromFile;
	bool updated=false;
	int line=1;
	while(!readfile.eof()) {
 		getline(readfile,lineFromFile);	
		if(!lineFromFile.empty()) {
		if(atoi(lineNumber.c_str())!=line) {
			fileData.push(lineFromFile);
		}
		else { 
			lineFromFile = updatedString;
			fileData.push(lineFromFile);
			updated=true;
		}
		line++;
	}
	}
	readfile.close();
	ofstream writefile;
	writefile.open(fileName,ios::trunc);
	while(!fileData.empty()) {
		writefile << fileData.front() <<endl;
		fileData.pop();
	}

	return updated;
}
	
void Storage::clearFile() {
	tasklist.clear();
	assert (tasklist.size() == 0);
}


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