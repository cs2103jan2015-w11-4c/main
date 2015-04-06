#include "Storage.h"
#include "Assert.h"
#include <vector>
#include <fstream>
#include <queue>
#include <boost/algorithm/string/trim.hpp>

using namespace std;

vector <string> Storage::tasklist;
const string IDENTIFIERS = "/";



bool Storage::writeFile(Task task, string outputfile,string filePath) {     //writes sentence into file
	
	//writing the new task into outputfile*
	ofstream myfile;				                    //open the file for output, declare an ofstream var  //write the new sentence into the file 
	outputfile = filePath + outputfile;   
	myfile.open(outputfile.c_str(),ios::app);           //open a file(my outputfile) with ofstream
	myfile << task.getDescription() << "/" << task.getDate() << "/" << lowerCase((task.getMonth()).substr(0,3)) << "/" << task.getYear() << "/" << task.getHour() << "/" << task.getMinute() << "/" << task.getStartHour() << "/" << task.getStartMinute() << "/" << task.getEndHour() << "/" << task.getEndMinute() << "/" << task.getStatus() << endl;
	myfile.close();

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

	if (readlineagain == (task.getDescription() + "/" + task.getDate() + "/" + lowerCase((task.getMonth()).substr(0,3)) + "/" + task.getYear() + "/" + task.getHour() + "/" + task.getMinute() + "/" + task.getStartHour() + "/" + task.getStartMinute() + "/" + task.getEndHour() + "/" + task.getEndMinute() + "/" + task.getStatus())) {
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



string Storage::readFile(string outputfile,string filePath) {				//display all items and return a string (fileContent)
	outputfile = filePath + outputfile;
	ifstream readfile(outputfile);
	string fileContent="";
	string line;
	//string taskDes,taskDate,taskMonth,taskYear , nextSubstring;
	if(readfile.peek()==std::ifstream::traits_type::eof()) {                //if file is empty
		cout << "Currently there are no tasks to be done. The file is empty." << endl << endl;
	}

	else {
		int lineNumber=1;
		while(!readfile.eof()) {
			getline(readfile,line);											//take line = sentence
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

	ifstream readfile(outputFile);
	if(readfile.peek() == std::ifstream::traits_type::eof()) {              	//if file is empty
		readfile.close();
		return true;
	}
	else {
		return false;                                                           //return success status
	}

}


//deletion, ignore same line and loop all other lines that's not deleted
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
	string line;
	istringstream data(newData);
	ofstream writefile;                                              //open w intention to write new updated information into file
	outputFile = filePath + outputFile;
	writefile.open(outputFile);
	while(getline(data,line)) {
		writefile << line << endl;                                   //newData (data) into output file
	}
	writefile.close();

	
	//checking if deleted successfully
	ifstream readfile(outputFile);        //reopen file
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

//change breakfast on 1 march to dinner date on 10 march
//update 1 dinner date on 10 march
bool Storage::updateFileData(string originalData , string updatedData,string outputFile,string filePath) {
	string fileData=readFile(outputFile,filePath);            //returns a string
	string lineFromFile;
	string newData="";
	boost::trim(originalData);                        //trim the line i want to find & replace
	istringstream in(fileData);                          //original line from file
 	while(getline(in,lineFromFile)) {                        //lines from in istringstream 
		string originalLine = lineFromFile;
		boost::trim(lineFromFile);                    
		if(lineFromFile!=originalData) {                   //trim line from file
			newData = newData + originalLine + "\n";            //not the line i wanna find to replace
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

	
	//checking if line is replaced
	ifstream readfile(outputFile);        //reopen file
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

string Storage::lowerCase(string input) {

	transform(input.begin(), input.end(), input.begin(), ::tolower);

	return input;
}


