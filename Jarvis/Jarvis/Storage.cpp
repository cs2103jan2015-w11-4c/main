#include "Storage.h"
#include "Assert.h"
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

vector <Task> Storage::tasklist;
const string IDENTIFIERS = "/";

bool Storage::writeFile(Task task, string outputfile,string filePath) {     //if adding/editing function, returns boolean value
	
	tasklist.push_back(task);
	
	int size;
	size = tasklist.size();
	//assert(size >= 1);

	//for (int i = 0; i < size; i++)
	//{
		//cout << tasklist[i] << endl;
	//}
	//Asert(i!=2);
	//start writing into myfile/
	ofstream myfile;//write the new sentence into the file
	outputfile = filePath + outputfile;
	myfile.open(outputfile.c_str(),ios::app);
	myfile << task.getDescription() << "/" << task.getDate() << "/" << task.getMonth() << "/" << task.getYear() << "/" << endl;
	//int i=0;
	//for (int i=0; i<size; i++) {
	//myfile << i+1 << "." << tasklist[i] << endl;      //write specific sentence in. naming like 1.meow   2. woof
	//}
	myfile.close();


	//if (tasklist[size-1]==(task)){                  //return status
		return true;
	//}
	//else {
		//return false;
//	}
}
int Storage::startIndex(string input) {
	
	return input.find_first_not_of(IDENTIFIERS);
}

int Storage::endIndex(string input) {
	return input.find_first_of(IDENTIFIERS);
}

string Storage::extractUserCommand(string input , string &substring) {
	int start;
	start = startIndex(input);
	int end;
	end = endIndex(input);
	substring = input.substr(end+1); 
	return input.substr(start,end-start);
}




//open file then print vector instead??
															
//vector <string> 
string Storage::readFile(string outputfile,string filePath) {				//display all items and return a VECTOR
	outputfile = filePath + outputfile;
	ifstream readfile(outputfile);
	string fileContent="";
	string line;
	string taskDes,taskDate,taskMonth,taskYear , nextSubstring;
	//char c;
	//If the file is empty
	if(readfile.peek()==std::ifstream::traits_type::eof()) {
		cout << outputfile << " is empty" << endl << endl;
	}

	else {
		int lineNumber=1;
		while(!readfile.eof()) {
			getline(readfile,line);
			if(!line.empty()) {
				/*taskDes = extractUserCommand(line, nextSubstring);
				line = nextSubstring;
				taskDate = extractUserCommand(line, nextSubstring);
				line = nextSubstring;
				taskMonth = extractUserCommand(line , nextSubstring);
				line = nextSubstring;
				taskYear = extractUserCommand(line , nextSubstring);
				fileContent = fileContent + to_string(lineNumber) + ". " + taskDes + " on " + taskDate + " " + taskMonth + " " + taskYear +"\n";*/
				fileContent = fileContent + line + "\n";
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






void Storage::clearFile(string outputFile,string filePath) {
	//outputFile = filePath + outputFile;
	ofstream writefile;
	writefile.open(outputFile,ios::trunc);
	writefile.close();
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

void Storage::replaceFileData(string newFileData,string outputFile,string filePath) {
	/*queue <string> fileData;
	string file=readFile(outputFile,filePath);
	string lineFromFile;
	string word;
	istringstream in(file);
 	while(getline(in,lineFromFile)) {	
		if(lineFromFile!=deletedLine) {
			fileData.push(lineFromFile);
		}
	}
	ofstream writefile;
	outputFile = filePath + outputFile;
	writefile.open(outputFile,ios::trunc);
	while(!fileData.empty()) {
		istringstream line((fileData.front()).substr(3));
		while(line>>word) {
				if(word!="on") {
					writefile << word << "/";
				}
			}
			writefile << endl;
			fileData.pop();
	}
	writefile.close();*/
	clearFile(outputFile,filePath);
	istringstream in(newFileData);
	string lineFromFile;
	ofstream writefile;
	outputFile = filePath + outputFile;
	writefile.open(outputFile);
	while(getline(in,lineFromFile)) {
		writefile << lineFromFile << endl;
	}


}