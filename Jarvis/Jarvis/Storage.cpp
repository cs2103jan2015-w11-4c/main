#include "Storage.h"
#include "Assert.h"
#include <vector>
#include <fstream>
#include <queue>
#include <boost/algorithm/string/trim.hpp>


using namespace std;

vector <string> Storage::tasklist;
const string IDENTIFIERS = "/";

//save information as dinner/30/june/2015
bool Storage::writeFile(Task task, string outputfile,string filePath) {     //writes sentence into file
	
	
	tasklist.push_back(task.getDescription() + "/" +  task.getDate() + "/" + task.getMonth() + "/" + task.getYear() + "/");

	//writing the new task into outputfile*
	ofstream myfile;				                    //open the file for output, declare an ofstream var  //write the new sentence into the file 
	outputfile = filePath + outputfile;   
	myfile.open(outputfile.c_str(),ios::app);           //open a file(my outputfile) with ofstream
	myfile << task.getDescription() << "/" << task.getDate() << "/" << task.getMonth() << "/" << task.getYear() << "/" << endl; //write to it
	myfile.close();                                     //close the file im writing into
	
	//checking success of writing into file
	ifstream readfile(outputfile);                      //outputfile is the name of the file where my data is stored. Open the file to READ
	string readLine = "";

	int i = 0;

	while(!readfile.eof()) {                     //final getline obtains a blank string. Reloop using i-1 to obtain last useful line
		getline(readfile, readLine);
		i++;
	} 
	readfile.close();

	ifstream readagain(outputfile);        //reopen file
	string readlineagain = "";

	for (int k=1; k < i; k++) {
		getline(readagain, readlineagain);
	}

	if (readlineagain == (task.getDescription()+"/"+task.getDate()+"/"+task.getMonth()+"/"+task.getYear()+"/")) {
		readagain.close();
		return true;
	}

	else {
		return false;
	}
	
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




string Storage::readFile(string outputfile,string filePath) {		  	//display all items and return a string (fileContent)
	outputfile = filePath + outputfile;
	ifstream readfile(outputfile);
	string fileContent="";
	string line;
	
	if(readfile.peek()==std::ifstream::traits_type::eof()) {              //if file is empty
		cout << outputfile << " is empty" << endl << endl;
	}

	else {
		int lineNumber=1;
		while(!readfile.eof()) {
			getline(readfile,line);                  //take line =  sentence
			if(!line.empty()) {
				
				fileContent = fileContent + line + "\n";                 //sending data back in a string   
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

	ifstream readfile(outputFile);
	if(readfile.peek() == std::ifstream::traits_type::eof()) {              	//if file is empty
		readfile.close();
		return true;
	}
	else {
		return false;                                                           //return success status
	}

}




void Storage::replaceFileData(string deletedData,string outputFile,string filePath) {
	string fileData=readFile(outputFile,filePath);
	string lineFromFile;
	string newData="";
	istringstream in(fileData);
	boost::trim(deletedData);
 	while(getline(in,lineFromFile)) {
		string originalLine = lineFromFile;
		boost::trim(lineFromFile);
		if(lineFromFile!=deletedData) {
			newData = newData + originalLine + "\n";
		}
	}
	clearFile(outputFile,filePath);
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

void Storage::updateFileData(string originalData , string updatedData,string outputFile,string filePath) {
	string fileData=readFile(outputFile,filePath);
	string lineFromFile;
	string newData="";
	boost::trim(originalData);
	istringstream in(fileData);
 	while(getline(in,lineFromFile)) {
		string originalLine = lineFromFile;
		boost::trim(lineFromFile);
		if(lineFromFile!=originalData) {
			newData = newData + originalLine + "\n";
		}
		else {
			newData = newData + updatedData + "\n";
		}
	}
	
	clearFile(outputFile,filePath);
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



