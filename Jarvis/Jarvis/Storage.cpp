//@author A0116114X
#include "Storage.h"
#include "Assert.h"
#include <vector>
#include <fstream>
#include <queue>
#include <boost/algorithm/string/trim.hpp>

using namespace std;

vector <string> Storage::tasklist;
const string IDENTIFIERS = "/";



bool Storage::writeFile(Task task, string outputfile,string filePath) {      //add function: writes sentence into file
	
	//writing new task into outputfile*
	ofstream myfile;				                                  //open the file for output, declare an ofstream var 
	outputfile = filePath + outputfile;   
	myfile.open(outputfile.c_str(),ios::app);                        //open a file(my outputfile) with ofstream
	myfile << task.getDescription() << "/" << task.getDate() << "/" << lowerCase((task.getMonth()).substr(0,3)) << "/" << task.getYear() << "/" << task.getHour() << "/" << task.getMinute() << "/" << task.getStartHour() << "/" << task.getStartMinute() << "/" << task.getEndHour() << "/" << task.getEndMinute() << "/" << task.getStatus() << endl;
	myfile.close();

	return checkAdd(task, outputfile,filePath);                      //checking function to return true if added
}




bool Storage::writeBackToFile(string deletedString, string fileName,string filePath) {
	ofstream myfile;
	fileName = filePath + fileName;
	myfile.open(fileName.c_str(),ios::app);
	myfile << deletedString << endl;
	return true;
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



string Storage::readFile(string outputfile,string filePath) {				//display all items and return a string (fileContent)
	outputfile = filePath + outputfile;
	ifstream readfile(outputfile);
	string fileContent="";
	string line;
	if(readfile.peek()==std::ifstream::traits_type::eof()) {                //if file is empty
		return "Error: Currently there are no tasks to be done. The file is empty.\n" ;
	}  else {

		int lineNumber=1;
		while(!readfile.eof()) {
			getline(readfile,line);	
			if(!line.empty()) {
				fileContent = fileContent + line + "\n";					//sending data back in a string 
				lineNumber++;			
			}
		}
	}
	readfile.close();
	return fileContent;

}
	





bool Storage::clearFile(string outputFile,string filePath) {
	outputFile = filePath + outputFile;                                         //get whole file path of file
	ofstream writefile;
	writefile.open(outputFile,ios::trunc);                                      //clear all contents of file
	writefile.close();

	return checkClear(outputFile, filePath);
}


//delete function, ignore same line and loop all other lines that's not deleted
bool Storage::replaceFileData(string deletedData,string outputFile,string filePath) {
	string fileData=readFile(outputFile,filePath);								//display data and return in string
	string lineFromFile;
	string newData="";
	istringstream in(fileData);
	boost::trim(deletedData);
 	while(getline(in,lineFromFile)) {								//using istringstream
		string originalLine = lineFromFile;                          //trim lines i obtain from my file cause i've also trimmed the line i wanna delete
		boost::trim(lineFromFile);
		if(lineFromFile!=deletedData) {
			newData = newData + originalLine + "\n";                 //compile the lines i dont intend to replace
		}
	}
	clearFile(outputFile,filePath);

	replaceData(deletedData, outputFile, filePath, newData);
	return checkDelete(deletedData, outputFile, filePath);

}





//update 1 task dinner date on 10 march : change breakfast on 1 march to dinner date on 10 march
bool Storage::updateFileData(string originalData, string updatedData,string outputFile,string filePath) {
	string fileData=readFile(outputFile,filePath);				     //returns a string
	string lineFromFile;
	string newData="";
	boost::trim(originalData);										 //trim the line i want to find & replace
	istringstream in(fileData);										 //original line from file
 	while(getline(in,lineFromFile)) {								 //lines from in istringstream 
		string originalLine = lineFromFile;
		boost::trim(lineFromFile);                    
		if(lineFromFile!=originalData) {						    //trim line from file
			newData = newData + originalLine + "\n";                //not the line i wanna find to replace
		} else {
			newData = newData + updatedData + "\n";
		}
	}
	clearFile(outputFile,filePath);

	replaceUpdateData(originalData, updatedData, outputFile, filePath, newData);
	return checkUpdate(originalData, updatedData, outputFile, filePath);
}




string Storage::lowerCase(string input) {

	transform(input.begin(), input.end(), input.begin(), ::tolower);

	return input;
}




bool Storage::checkAdd(Task task, string outputfile,string filePath) {   
	ifstream readfile(outputfile);                                   //outputfile is the name of the file where data is stored. Open file to READ
	string readLine = "";
	int i = 0;

	while(!readfile.eof()) {						                //final getline obtains a blank string. Reloop using i-1 to obtain last meaningful line
		getline(readfile, readLine);
		i++;
	} 
	readfile.close();
	ifstream readagain(outputfile);									 //reopen file
	string readlineagain = "";

	for (int k=1; k < i; k++) {
		getline(readagain, readlineagain);
	}

	if (readlineagain == (task.getDescription() + "/" + task.getDate() + "/" + lowerCase((task.getMonth()).substr(0,3)) + "/" + task.getYear() + "/" + task.getHour() + "/" + task.getMinute() + "/" + task.getStartHour() + "/" + task.getStartMinute() + "/" + task.getEndHour() + "/" + task.getEndMinute() + "/" + task.getStatus())) {
		readagain.close();
		return true;
	}  else {
		return false;
	} 
}





bool Storage::checkClear(string outputFile,string filePath) {
	ifstream readfile(outputFile);
	assert(readfile.peek() == std::ifstream::traits_type::eof());
	if(readfile.peek() == std::ifstream::traits_type::eof()) {              	//if file is empty
		readfile.close();
		return true;
	}
	else {
		return false;                                                           //return success status
	}
}




bool Storage::checkDelete(string deletedData,string outputFile,string filePath) {
		ifstream readfile(outputFile);											 //reopen file
	string readline = "";

	while (!readfile.eof()) {
		getline(readfile, readline);
		if (readline == deletedData) {
			readfile.close();
			return false;
		}
	}
			readfile.close();
			return true;

}



bool Storage::checkUpdate(string originalData, string updatedData,string outputFile,string filePath) {
		ifstream readfile(outputFile);											   //reopen file
		string readline = "";

		while (!readfile.eof()) {
		getline(readfile, readline);
		if (readline == updatedData) {
			readfile.close();
			return true;
		}
	}
			readfile.close();
			return false;
}
			



		
void Storage::replaceData (string deletedData,string outputFile,string filePath, string newData) {
	string line;
	istringstream data(newData);
	ofstream writefile;												          //open w intention to write new updated information into file
	outputFile = filePath + outputFile;
	writefile.open(outputFile);
	while(getline(data,line)) {
		writefile << line << endl;										    //newData (data) into output file
	}
	writefile.close();

}


void Storage::replaceUpdateData(string originalData, string updatedData,string outputFile,string filePath, string newData) {
	string line;
	istringstream data(newData);
	ofstream writefile;
	outputFile = filePath + outputFile;
	writefile.open(outputFile);
	while(getline(data,line)) {
		writefile << line << endl;
	}
	writefile.close();
}