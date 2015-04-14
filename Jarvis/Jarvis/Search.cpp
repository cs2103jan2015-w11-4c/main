//@author A0118904E
#include "Search.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

const string ERROR_MSG = " * do not exist in file\n";

Search::Search() {

}

Search::Search(Task taskObject) {
	T1 = taskObject;
}

Search::~Search() {

}

//This function searches for tasks that have atleast 1 of the keywords specified by the user
string Search::execute(string fileName,string filePath) {
	string fileData = S1.readFile(fileName,filePath);
	string linesWithWords="" ;
	string keywordsToSearch = T1.getKeywords();
	string line,token;
	vector <string> tokens;
	string delimiter = "/ ";
	bool isFound;
	istringstream in(fileData);
	//If atleast one keyword is found in the task, it is returned to the user
	while(getline(in, line)) {
		istringstream word(keywordsToSearch);
		while (word>>token) {
			boost::trim(token);
			tokens = extractWord(line,delimiter);
			while(!tokens.empty()) {
				boost::trim(tokens.back());
				if(changeToLowerCase(tokens.back())==changeToLowerCase(token)) {
					linesWithWords = linesWithWords + line + "\n";
					isFound=true;
					break;
				} else {
					isFound=false;
				}
				tokens.pop_back();
			}
			if(isFound==true) {
				break;
			}
		}
    }
	//If the keyword does not exist in the user's task list, it returns an error message
	if(linesWithWords=="") {
		return  "Error: The words * " + keywordsToSearch + ERROR_MSG; 
	} else {
	   return linesWithWords;
	}		
}

//Each task line is read word by word
//This breaks the entire task line in the file into tokens separated by spaces
vector <string> Search::extractWord(string input,string delimiter) {
	vector<string> tokens;
	boost::split(tokens,input, boost::is_any_of(delimiter));
	return tokens;
}



//This function searches for tasks that have ALL the keywords specified by the user in its deadline
//Display uses this particulary to find tasks of a particular deadline(date, month, year or a combination of these)
string Search::executeSearch(string fileName,string filePath) {
	string fileData = S1.readFile(fileName,filePath);
	string linesWithWords="" ;
	string keywordsToSearch = T1.getKeywords();
	string line,token;
	vector <string> tokens;
	string delimiter = "/";
	bool isFound;
	//Count makes sure that only the three tokens (date,month,year) are checked.
	int count=0;
	istringstream in(fileData);
	//Only when all keywords are found in the deadline is the task displayed to the user
	//Each line is broken into words and then checked
	while(getline(in, line)) {
		istringstream word(keywordsToSearch);
		while (word>>token) {
			count=0;
			tokens = extractWord(line,delimiter);
			reverse(tokens.begin(),tokens.end());
			tokens.pop_back();
			while(count<3 && !tokens.empty()) {
				if(changeToLowerCase(tokens.back())==changeToLowerCase(token)) {
					isFound=true;
					break;
				}else {
					isFound=false;
				}
				count++;
				tokens.pop_back();
			}
			if(isFound==false) {
				break;
			}
		}
		//If all the deadline tokens specified by the user are found in the task , it is added to this string to give back to the user
		if(isFound) {
			linesWithWords = linesWithWords + line + "\n";
		}
	}
	   return linesWithWords;

}

//Changes all tokens to lower case
//This allows the user input to not be case sensitive
string Search::changeToLowerCase(string input) {
	string lowerCase="";
	for(int i=0;i<input.size();i++) {
		if(input[i]>='A' && input[i]<='Z') {
			input[i] = tolower(input[i]);
			lowerCase = lowerCase + input[i];
		}
		else {
			lowerCase = lowerCase + input[i];
		}
	}
	return lowerCase;
}